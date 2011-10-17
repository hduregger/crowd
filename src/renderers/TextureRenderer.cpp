#include "TextureRenderer.h"

#include "../graphics/OpenGL.h"
#include "../Error.h"


TextureRenderer::TextureRenderer(   GLfloat                     viewportSize,
                                    const Texture*              texture,
                                    const std::vector<QString>& vertexShaderFilenames,
                                    const std::vector<QString>& fragmentShaderFilenames,
                                    QString                     programName,
                                    bool                        isValueRenderer)
:   shaderProgram(0),
    vertexArrayObject(0),
    attribVertex(-1),
    attribTexCoord(-1),
    arrayBufferVertices(0),
    arrayBufferTexCoords(0),
    texture(texture),
    totalBufferSize(0),
    vertexShader(0),
    fragmentShader(0),
    uniformCameraPosition(-1),
    uniformSize(-1),
    camera(NULL),
    viewportSize(viewportSize),
    isValueRendering(isValueRenderer)
{
    initCamera();
    initShaderProgram(vertexShaderFilenames, fragmentShaderFilenames, programName);
    initAttribs();
    initVBO();
    initUniforms();
}


TextureRenderer::~TextureRenderer()
{
    delete shaderProgram;
    delete fragmentShader;
    delete vertexShader;

    delete camera;

    glDeleteBuffers(1, &arrayBufferVertices);
    glDeleteBuffers(1, &arrayBufferTexCoords);

    glDeleteVertexArrays(1, &vertexArrayObject);
}


void TextureRenderer::setCameraPosition(GLfloat x, GLfloat y)
{
    shaderProgram->enable();

    glUniform3f(uniformCameraPosition, x, y, 0.0f);
    GL_ERROR;
}


void TextureRenderer::render()
{
    shaderProgram->enable();

    glBindVertexArray(vertexArrayObject);
    GL_ERROR;

    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferVertices);
    GL_ERROR;

    glVertexAttribPointer(attribVertex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    GL_ERROR;

    glEnableVertexAttribArray(attribVertex);
    GL_ERROR;

    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferTexCoords);
    GL_ERROR;

    glVertexAttribPointer(attribTexCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    GL_ERROR;

    glEnableVertexAttribArray(attribTexCoord);
    GL_ERROR;

    glActiveTexture(GL_TEXTURE0);
    GL_ERROR;
    texture->enable();

    glDrawArrays(GL_TRIANGLES, 0, 6);
    GL_ERROR;

    glDisableVertexAttribArray(attribVertex);
    GL_ERROR;
    glDisableVertexAttribArray(attribTexCoord);
    GL_ERROR;

    texture->disable();

    glBindVertexArray(0);
}


void TextureRenderer::initUniforms()
{
    GLint loc;

    loc = shaderProgram->getUniformLocation(Camera::CAMERA_PROJECTION);

    glUniformMatrix4fv(loc, 1, GL_FALSE, camera->projection);
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("textureSampler");
    // Set to texture image unit 0
    glUniform1i( loc, 0 );
    GL_ERROR;


    if (texture->isBufferTexture())
    {
        uniformSize = shaderProgram->getUniformLocation("BUFFER_SIZE");

        glUniform1i( uniformSize, viewportSize );
        GL_ERROR;
    }

    uniformCameraPosition = shaderProgram->getUniformLocation("camera.position");

    glUniform3f(uniformCameraPosition, 0.0f, 0.0f, 0.0f);
    GL_ERROR;
}


void TextureRenderer::initCamera()
{
    camera = new Camera();

    camera->setOrthogonalProjection(0.0f, viewportSize, 0.0f, viewportSize, -1.0f, 1.0f);
}


void TextureRenderer::initVBO()
{
    glGenVertexArrays(1, &vertexArrayObject);
    GL_ERROR;

    glBindVertexArray(vertexArrayObject);
    GL_ERROR;

    GLfloat points[] = {
    0.0f, 0.0f, 0.0f, 1.0f,
    viewportSize, 0.0f, 0.0f, 1.0f,
    viewportSize, viewportSize, 0.0f, 1.0f,

    0.0f,  0.0f, 0.0f, 1.0f,
    viewportSize,   viewportSize, 0.0f, 1.0f,
    0.0f,   viewportSize, 0.0f, 1.0f };

    GLfloat texture_coordinates[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f };

    glGenBuffers(1, &arrayBufferVertices);
    GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferVertices);
    GL_ERROR;
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(GLfloat), reinterpret_cast<GLfloat*> (points), GL_STATIC_DRAW);
    GL_ERROR;
    totalBufferSize += 6 * 4 * sizeof(GLfloat);
    glVertexAttribPointer(attribVertex, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    GL_ERROR;
//    glEnableVertexAttribArray(attribVertex);
//    GL_ERROR;

    glGenBuffers(1, &arrayBufferTexCoords);
    GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, arrayBufferTexCoords);
    GL_ERROR;
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(GLfloat), reinterpret_cast<GLfloat*> (texture_coordinates), GL_STATIC_DRAW);
    GL_ERROR;
    totalBufferSize += 6 * 2 * sizeof(GLfloat);
    glVertexAttribPointer(attribTexCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    GL_ERROR;
//    glEnableVertexAttribArray(attribTexCoord);
//    GL_ERROR;

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    GL_ERROR;

}


void TextureRenderer::initShaderProgram(const std::vector<QString>& vertexShaderFilenames, const std::vector<QString>& fragmentShaderFilenames, QString programName)
{
    //
    // Create shader program
    //

    vertexShader    = new VertexShader(vertexShaderFilenames);
    fragmentShader  = new FragmentShader(fragmentShaderFilenames);

    shaderProgram = new ShaderProgram(programName);

    shaderProgram->attach(vertexShader);
    shaderProgram->attach(fragmentShader);

    shaderProgram->link();

    shaderProgram->enable();
}


void TextureRenderer::initAttribs()
{
    attribVertex   = shaderProgram->getAttribLocation("_vertex");
    attribTexCoord = shaderProgram->getAttribLocation("_texCoord");
}


void TextureRenderer::setColorScaleMin(float)
{
}


void TextureRenderer::setColorScaleMax(float)
{
}


float TextureRenderer::getColorScaleMin() const
{
    return 0.0f;
}


float TextureRenderer::getColorScaleMax() const
{
    return 0.0f;
}


void TextureRenderer::setAlpha(GLfloat)
{
}


bool TextureRenderer::isValueRenderer() const
{
    return isValueRendering;
}


int TextureRenderer::getTotalBufferSize()
{
    return totalBufferSize;
}
