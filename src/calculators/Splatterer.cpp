#include <QDebug>
#include <QImage>

#include "Splatterer.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"
#include "../Vector4.h"
#include "../Exception.h"
#include "../Error.h"
#include "SharedBufferCalculator.h"


#include <CL/cl_gl.h>


Splatterer::Splatterer( const Logger*       logger,
                        const Context*      context,
                        GLfloat             viewportSize,
                        QString             textureFilename,
                        BufferTexture*      baseDiscomfort)
:   pointBuffer(0),
    screenSizedQuadBuffer(0),
    framebufferObject(0),
    densityDiscomfortVelocity(NULL),
    splatAreas(NULL),
    agent(NULL),
    splatAttribVertex(-1),
    splatProgram(NULL),
    splatVertexShader(NULL),
    splatGeometryShader(NULL),
    splatFragmentShader(NULL),
    camera(NULL),
    bufferSideLength(viewportSize),
    totalBufferSize(0),
    densityDiscomfortVelocityTripple(NULL),
    logger(logger),
    context(context),
    prepareFramebufferRenderer(NULL),
    discomfortProgram(NULL),
    discomfortVertexShader(NULL),
    discomfortGeometryShader(NULL),
    discomfortFragmentShader(NULL),
    discomfortFactor(NULL),
    discomfortRadius(NULL),
    discomfortPosition(NULL)
{
    attachments[0] = GL_COLOR_ATTACHMENT0;
    attachments[1] = GL_COLOR_ATTACHMENT1;

    initCamera();
    initSplatShaderProgram();
    initAttribs();
    initVBO();
    initUniforms();
    initFramebufferObject();

    try
    {
        //
        // Create splatted texture
        //

        QImage image = Texture::loadTexture(textureFilename, false, true);

        uint pixelCount = image.width() * image.height();

        std::vector<float> data(pixelCount * 4);

        Texture::convertToFloats(image, data, pixelCount);

        glActiveTexture(GL_TEXTURE0);

        agent = new Texture2D(image.width(), image.height(), GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR, GL_RGBA32F, GL_RGBA, GL_FLOAT, &data[0]);
        totalBufferSize += image.width() * image.height() * 4 * 4;

    }
    catch (Exception& e)
    {
        throw Exception("Could not load splatting texture: " + e.message);
    }

    //
    // Create buffer object for density, discomfort and velocity
    //

    size_t bufferByteSize = bufferSideLength * bufferSideLength * sizeof(GLfloat) * 4;

    densityDiscomfortVelocityTripple = new TextureBufferTripple(bufferByteSize, NULL, GL_DYNAMIC_COPY, GL_RGBA32F, CL_MEM_READ_WRITE, context);
    totalBufferSize += bufferByteSize;

    //
    // Create renderer to render base discomfort map to framebuffer
    //

    std::vector<QString> filenamesVert;
    std::vector<QString> filenamesFrag;

    filenamesVert.push_back("src/shaders/shared.vert");
    filenamesFrag.push_back("src/shaders/shared.frag");
    filenamesFrag.push_back("src/shaders/prepareFramebuffer.frag");

    prepareFramebufferRenderer = new TextureRenderer(bufferSideLength, baseDiscomfort, filenamesVert, filenamesFrag, "Framebuffer Preparation Shader", false);

    //
    // Create shader to render discomfort at pointer to framebuffer
    //

    initDiscomfortShaderProgram();
}


Splatterer::~Splatterer()
{
    delete splatProgram;
    delete splatVertexShader;
    delete splatGeometryShader;
    delete splatFragmentShader;

    delete discomfortProgram;
    delete discomfortVertexShader;
    delete discomfortGeometryShader;
    delete discomfortFragmentShader;

    delete densityDiscomfortVelocity;
    delete splatAreas;
    delete agent;

    delete densityDiscomfortVelocityTripple;

    delete camera;

    delete prepareFramebufferRenderer;

    glDeleteBuffers(1, &pointBuffer);
    glDeleteBuffers(1, &screenSizedQuadBuffer);
    glDeleteFramebuffers(1, &framebufferObject);
}


const Texture2D* Splatterer::getDensitiesDiscomfortsVelocities() const
{
    return densityDiscomfortVelocity;
}


const Texture2D* Splatterer::getSplatAreas() const
{
    return splatAreas;
}


const BufferTexture* Splatterer::getAverageVelocities() const
{
    return densityDiscomfortVelocityTripple->getBufferTexture();
}


void Splatterer::splat( GLuint                  count,
                        const BufferTexture*    positions,
                        const BufferTexture*    directions,
                        const BufferTexture*    speeds,
                        const BufferTexture*    ids,
                        const BufferTexture*    radii        )
{
    glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);
    GL_ERROR;

    glVertexAttribPointer(splatAttribVertex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    GL_ERROR;

    glEnableVertexAttribArray(splatAttribVertex);
    GL_ERROR;

    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_BLEND);
    GL_ERROR;

    glActiveTexture(GL_TEXTURE0);
    GL_ERROR;
    positions->enable();

    glActiveTexture(GL_TEXTURE1);
    GL_ERROR;
    directions->enable();

    glActiveTexture(GL_TEXTURE2);
    GL_ERROR;
    speeds->enable();

    glActiveTexture(GL_TEXTURE3);
    GL_ERROR;
    ids->enable();

    glActiveTexture(GL_TEXTURE4);
    GL_ERROR;
    radii->enable();

    glActiveTexture(GL_TEXTURE5);
    GL_ERROR;
    agent->enable();

    // Draw discomfort brush

    discomfortProgram->enable();

    glDrawArraysInstanced(GL_POINTS, 0, 1, 1);
    GL_ERROR;

    // Draw agent splats

    splatProgram->enable();

    glDrawArraysInstanced(GL_POINTS, 0, 1, count);
    GL_ERROR;

    glDisable(GL_BLEND);
    GL_ERROR;

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    GL_ERROR;

    glDisableVertexAttribArray(splatAttribVertex);
    GL_ERROR;

    glBindTexture(GL_TEXTURE_BUFFER, 0);
}


void Splatterer::initVBO()
{
    glGenBuffers(1, &pointBuffer);
    GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);
    GL_ERROR;

    GLfloat points[] = { 0.0f,  0.0f, 0.0f, 1.0f };

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(GLfloat), reinterpret_cast<GLfloat*> (points), GL_DYNAMIC_COPY);
    GL_ERROR;
    totalBufferSize += 4 * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glGenBuffers(1, &screenSizedQuadBuffer);
    GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, screenSizedQuadBuffer);
    GL_ERROR;

    GLfloat points2[] = { 0.0f,              0.0f,             0.0f, 1.0f,
                          bufferSideLength,  0.0f,             0.0f, 1.0f,
                          bufferSideLength,  bufferSideLength, 0.0f, 1.0f,
                          0.0f,              bufferSideLength, 0.0f, 1.0f  };

    glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(GLfloat), reinterpret_cast<GLfloat*> (points2), GL_DYNAMIC_COPY);
    GL_ERROR;
    totalBufferSize += 4 * 4 * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void Splatterer::initSplatShaderProgram()
{
    // Create splat shader

    std::vector<QString> filenamesVert;
    filenamesVert.push_back("src/shaders/splatterer.vert");

    std::vector<QString> filenamesGeom;
    filenamesGeom.push_back("src/shaders/splatterer.geom");

    std::vector<QString> filenamesFrag;
    filenamesFrag.push_back("src/shaders/shared.frag");
    filenamesFrag.push_back("src/shaders/splatterer.frag");

    splatVertexShader    = new VertexShader(filenamesVert);
    splatGeometryShader  = new GeometryShader(filenamesGeom);
    splatFragmentShader  = new FragmentShader(filenamesFrag);

    splatProgram = new ShaderProgram("Splatterer Splat Shader Program");

    splatProgram->attach(splatVertexShader);
    splatProgram->attach(splatGeometryShader);
    splatProgram->attach(splatFragmentShader);

    splatProgram->link();

    splatProgram->enable();
}


void Splatterer::initDiscomfortShaderProgram()
{
    // Create discomfort shader

    std::vector<QString> filenamesVert;
    filenamesVert.push_back("src/shaders/discomfortSplat.vert");

    std::vector<QString> filenamesGeom;
    filenamesGeom.push_back("src/shaders/discomfortSplat.geom");

    std::vector<QString> filenamesFrag;
    filenamesFrag.push_back("src/shaders/shared.frag");
    filenamesFrag.push_back("src/shaders/discomfortSplat.frag");

    discomfortVertexShader    = new VertexShader(filenamesVert);
    discomfortGeometryShader  = new GeometryShader(filenamesGeom);
    discomfortFragmentShader  = new FragmentShader(filenamesFrag);

    discomfortProgram = new ShaderProgram("Splatterer Discomfort Splat Shader Program");

    discomfortProgram->attach(discomfortVertexShader);
    discomfortProgram->attach(discomfortGeometryShader);
    discomfortProgram->attach(discomfortFragmentShader);

    discomfortProgram->link();

    discomfortProgram->enable();

    GLint loc;

    loc = discomfortProgram->getUniformLocation(Camera::CAMERA_PROJECTION);

    glUniformMatrix4fv(loc, 1, GL_FALSE, camera->projection);
    GL_ERROR;

    loc = discomfortProgram->getUniformLocation("camera.position");

    glUniform3f(loc, 0.0f, 0.0f, 0.0f);
    GL_ERROR;

    loc = discomfortProgram->getUniformLocation("agent");

    // Set to texture image unit 5
    glUniform1i( loc, 5 );
    GL_ERROR;

    discomfortFactor = new FloatUniform(discomfortProgram, "factor");
    discomfortFactor->set(discomfortProgram, 100.0f);

    discomfortRadius = new FloatUniform(discomfortProgram, "radius");
    discomfortRadius->set(discomfortProgram, 3.0f);

    discomfortPosition = new Vec2Uniform(discomfortProgram, "position");
    discomfortPosition->set(discomfortProgram, 100.0f, 100.0f);
}


void Splatterer::initCamera()
{
     camera = new Camera();

     camera->setOrthogonalProjection(0.0f, bufferSideLength, 0.0f, bufferSideLength, -1.0f, 1.0f);
}


void Splatterer::initUniforms()
{
    splatProgram->enable();

    GLint loc;

    loc = splatProgram->getUniformLocation(Camera::CAMERA_PROJECTION);

    glUniformMatrix4fv(loc, 1, GL_FALSE, camera->projection);
    GL_ERROR;

    loc = splatProgram->getUniformLocation("camera.position");

    glUniform3f(loc, 0.0f, 0.0f, 0.0f);
    GL_ERROR;

    loc = splatProgram->getUniformLocation("positions");

    // Set to texture image unit 0
    glUniform1i( loc, 0 );
    GL_ERROR;

    loc = splatProgram->getUniformLocation("directions");

    // Set to texture image unit 1
    glUniform1i( loc, 1 );
    GL_ERROR;

    loc = splatProgram->getUniformLocation("speeds");

    // Set to texture image unit 2
    glUniform1i( loc, 2 );
    GL_ERROR;

    loc = splatProgram->getUniformLocation("ids");

    // Set to texture image unit 3
    glUniform1i( loc, 3 );
    GL_ERROR;

    loc = splatProgram->getUniformLocation("radii");

    // Set to texture image unit 4
    glUniform1i( loc, 4 );
    GL_ERROR;

    loc = splatProgram->getUniformLocation("agent");

    // Set to texture image unit 5
    glUniform1i( loc, 5 );
    GL_ERROR;
}


void Splatterer::initAttribs()
{
    // Note: due to a bug in the Catalyst drivers attrib name had to be alphabetically
    //       before gl_ names or things like gl_instanceID will mess up (probably fixed now)
    //       also at least 1 attrib must be bound
    splatAttribVertex = splatProgram->getAttribLocation("_vertex");
}


void Splatterer::initFramebufferObject()
{
    glGenFramebuffers(1, &framebufferObject);
    GL_ERROR;

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferObject);
    GL_ERROR;

    glActiveTexture(GL_TEXTURE0);

    //
    // Create density, discomfort and velocites texture attachment
    //

    densityDiscomfortVelocity = new Texture2D(bufferSideLength, bufferSideLength, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST, GL_RGBA32F, GL_RGBA, GL_FLOAT, NULL);
    totalBufferSize += bufferSideLength * bufferSideLength * 4 * 4;

    densityDiscomfortVelocity->attachToActiveFramebuffer(GL_COLOR_ATTACHMENT0);

    GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

    if (status == 0)
    {
        throw Exception("OpenGL error caused failure to check framebuffer status of 'framebufferObject' in Splatterer after creating densityDiscomfortVelocity attachment");
    }
    else if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw Exception("Framebuffer 'framebufferObject' is incomplete after creating densityDiscomfortVelocity attachment: " + OpenGL::getFramebufferStatusString(status));
    }

    //
    // Create agent texture attachment
    //

    splatAreas = new Texture2D(bufferSideLength, bufferSideLength, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    totalBufferSize += bufferSideLength * bufferSideLength * 4 * 1;

    splatAreas->attachToActiveFramebuffer(GL_COLOR_ATTACHMENT1);

    status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

    if (status == 0)
    {
        throw Exception("OpenGL error caused failure to check framebuffer status of 'framebufferObject' in Splatterer after creating agent attachment");
    }
    else if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw Exception("Framebuffer 'framebufferObject' is incomplete after creating agent attachment: " + OpenGL::getFramebufferStatusString(status));
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}


int Splatterer::getTotalBufferSize()
{
    return totalBufferSize;
}


void Splatterer::prepareFramebuffer()
{
    glViewport(0, 0, bufferSideLength, bufferSideLength);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferObject);
    GL_ERROR;

    glDrawBuffers(2, attachments);
    GL_ERROR;

    prepareFramebufferRenderer->render();
}


void Splatterer::copyDataFromFramebuffer()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebufferObject);
    GL_ERROR;

    // Copy density and discomfort into OpenCL buffer (I think this would not be required if we would
    // use images in OpenCL instead of buffers)

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    GL_ERROR;

    glBindBuffer(GL_PIXEL_PACK_BUFFER, densityDiscomfortVelocityTripple->getBuffer());
    GL_ERROR;

    glReadPixels(0, 0, bufferSideLength, bufferSideLength, GL_RGBA, GL_FLOAT, NULL);
    GL_ERROR;

    // Reset buffers

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    GL_ERROR;

    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    GL_ERROR;

    glReadBuffer(GL_BACK);
    GL_ERROR;
}


cl_mem Splatterer::getDensitiesDiscomfortsVelocitiesShared()
{
    return densityDiscomfortVelocityTripple->getBufferShared();
}



Vector4 Splatterer::getDensityDiscomfortVelocity(cl_uint positionX, cl_uint positionY)
{
    return SharedBufferCalculator::getValue(densityDiscomfortVelocityTripple->getBuffer(), positionX, positionY, GL_RGBA32F, bufferSideLength);
}


void Splatterer::setDiscomfortBrushRadius(float radius) const
{
    discomfortRadius->set(discomfortProgram, radius);
}


void Splatterer::setDiscomfortBrushIntensity(float intensity) const
{
    discomfortFactor->set(discomfortProgram, intensity);
}


void Splatterer::setDiscomfortBrushPosition(float x, float y) const
{
    discomfortPosition->set(discomfortProgram, x, y);
}

