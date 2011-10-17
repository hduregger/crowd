#include "AgentsRenderer.h"

#include "../graphics/OpenGL.h"
#include "../Exception.h"
#include "../Error.h"


AgentsRenderer::AgentsRenderer( GLfloat domainSize, const Settings* settings)
:   pointBuffer(0),
    attribVertex(-1),
    shaderProgram(NULL),
    vertexShader(NULL),
    geometryShader(NULL),
    fragmentShader(NULL),
    camera(NULL),
    totalBufferSize(0)
{
    initCamera(domainSize);
    initShaderProgram();
    initAttribs();
    initVBO();
    initUniforms();

    agent0 = initializeAgentTexture(settings->agentsGroup0Texture);
    agent1 = initializeAgentTexture(settings->agentsGroup1Texture);
    agent2 = initializeAgentTexture(settings->agentsGroup2Texture);
    agent3 = initializeAgentTexture(settings->agentsGroup3Texture);
}


AgentsRenderer::~AgentsRenderer()
{
    delete shaderProgram;
    delete vertexShader;
    delete geometryShader;
    delete fragmentShader;

    delete agent0;
    delete agent1;
    delete agent2;
    delete agent3;

    delete camera;

    glDeleteBuffers(1, &pointBuffer);
}


Texture2D* AgentsRenderer::initializeAgentTexture(QString textureFilename)
{
    try
    {
        QImage image = Texture::loadTexture(textureFilename, false, false);

        uint pixelCount = image.width() * image.height();

        std::vector<float> data(pixelCount * 4);

        Texture::convertToFloats(image, data, pixelCount);

        totalBufferSize += image.width() * image.height() * 4 * 4;


        return new Texture2D(image.width(), image.height(), GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGBA, GL_RGBA, GL_FLOAT, &data[0]);
    }
    catch (Exception& e)
    {
        throw Exception("Could not load agent texture: " + e.message);
    }
}


void AgentsRenderer::initVBO()
{
    glGenBuffers(1, &pointBuffer);
    GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);
    GL_ERROR;

    GLfloat points[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(GLfloat), reinterpret_cast<GLfloat*> (points), GL_DYNAMIC_COPY);
    GL_ERROR;
    totalBufferSize += 4 * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void AgentsRenderer::initShaderProgram()
{
    std::vector<QString> filenamesVert;
    filenamesVert.push_back("src/shaders/agents.vert");

    std::vector<QString> filenamesGeom;
    filenamesGeom.push_back("src/shaders/agents.geom");

    std::vector<QString> filenamesFrag;
    filenamesFrag.push_back("src/shaders/shared.frag");
    filenamesFrag.push_back("src/shaders/agents.frag");

    vertexShader    = new VertexShader(filenamesVert);
    geometryShader  = new GeometryShader(filenamesGeom);
    fragmentShader  = new FragmentShader(filenamesFrag);

    shaderProgram = new ShaderProgram("Agents Shader Program");

    shaderProgram->attach(vertexShader);
    shaderProgram->attach(geometryShader);
    shaderProgram->attach(fragmentShader);

    shaderProgram->link();

    shaderProgram->enable();
}


void AgentsRenderer::initCamera(GLfloat domainSize)
{
     camera = new Camera();

     camera->setOrthogonalProjection(0.0f, domainSize, 0.0f, domainSize, -1.0f, 1.0f);
}


void AgentsRenderer::initUniforms()
{
    GLint loc;

    loc = shaderProgram->getUniformLocation(Camera::CAMERA_PROJECTION);

    glUniformMatrix4fv(loc, 1, GL_FALSE, camera->projection);
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("camera.position");

    glUniform3f(loc, 0.0f, 0.0f, 0.0f);
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("positions");

    // Set to texture image unit 0
    glUniform1i( loc, 0 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("directions");

    // Set to texture image unit 1
    glUniform1i( loc, 1 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("ids");

    // Set to texture image unit 2
    glUniform1i( loc, 2 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("radii");

    // Set to texture image unit 3
    glUniform1i( loc, 3 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("agent0");

    // Set to texture image unit 4
    glUniform1i( loc, 4 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("agent1");

    // Set to texture image unit 5
    glUniform1i( loc, 5 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("agent2");

    // Set to texture image unit 6
    glUniform1i( loc, 6 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("agent3");

    // Set to texture image unit 7
    glUniform1i( loc, 7 );
    GL_ERROR;
}


void AgentsRenderer::initAttribs()
{
    // Note: due to a bug in the Catalyst drivers attrib name had to be alphabetically
    // before gl_ names or things like gl_instanceID will mess up (probably fixed now)
    // also at least 1 attrib must be bound
    attribVertex = shaderProgram->getAttribLocation("_vertex");
}


void AgentsRenderer::render(GLuint                  count,
                            const BufferTexture*    positions,
                            const BufferTexture*    directions,
                            const BufferTexture*    ids,
                            const BufferTexture*    radii        ) const
{
    shaderProgram->enable();

    glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);
    GL_ERROR;

    glVertexAttribPointer(attribVertex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    GL_ERROR;

    glEnableVertexAttribArray(attribVertex);
    GL_ERROR;

    glActiveTexture(GL_TEXTURE0);
    GL_ERROR;
    positions->enable();

    glActiveTexture(GL_TEXTURE1);
    GL_ERROR;
    directions->enable();

    glActiveTexture(GL_TEXTURE2);
    GL_ERROR;
    ids->enable();

    glActiveTexture(GL_TEXTURE3);
    GL_ERROR;
    radii->enable();

    glActiveTexture(GL_TEXTURE4);
    GL_ERROR;
    agent0->enable();

    glActiveTexture(GL_TEXTURE5);
    GL_ERROR;
    agent1->enable();

    glActiveTexture(GL_TEXTURE6);
    GL_ERROR;
    agent2->enable();

    glActiveTexture(GL_TEXTURE7);
    GL_ERROR;
    agent3->enable();

    glDrawArraysInstanced(GL_POINTS, 0, 1, count);
    GL_ERROR;

    glDisableVertexAttribArray(attribVertex);
    GL_ERROR;

    glBindTexture(GL_TEXTURE_BUFFER, 0);
}


int AgentsRenderer::getTotalBufferSize()
{
    return totalBufferSize;
}
