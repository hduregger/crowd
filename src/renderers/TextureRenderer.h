#ifndef TEXTURERENDERER_H_
#define TEXTURERENDERER_H_

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"

#include "../graphics/Texture2D.h"
#include "../graphics/Camera.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/VertexShader.h"
#include "../graphics/FragmentShader.h"


class TextureRenderer
{
public:

    /**
     * isValueRenderer is true if the renderer is displaying single values else it displays vectors.
     */

                    TextureRenderer(GLfloat                     viewportSize,
                                    const Texture*              texture,
                                    const std::vector<QString>& vertexShaderFilenames,
                                    const std::vector<QString>& fragmentShaderFilenames,
                                    QString                     programName,
                                    bool                        isValueRenderer);
    virtual         ~TextureRenderer();


    void            setCameraPosition(GLfloat x, GLfloat y);

    virtual void    render();

    /**
     * Returns true if the renderer is displaying single values else it displays vectors.
     * This is used by CrowdScene to distinguish GUI element control.
     */

    bool            isValueRenderer() const;

    //
    // These members do nothing in the default implementation and
    // only return dummy values. This is for interface compatibility
    // to lower code complexity in the using class.
    //

    virtual void    setColorScaleMin(float min);
    virtual void    setColorScaleMax(float max);

    virtual float   getColorScaleMin() const;
    virtual float   getColorScaleMax() const;

    virtual void    setAlpha(GLfloat alpha);


    virtual int     getTotalBufferSize();

protected:

    ShaderProgram*      shaderProgram;

    GLuint              vertexArrayObject;

    GLint               attribVertex;
    GLint               attribTexCoord;

    GLuint              arrayBufferVertices;
    GLuint              arrayBufferTexCoords;

    const Texture*      texture;

    int                 totalBufferSize;

private:

    VertexShader*       vertexShader;
    FragmentShader*     fragmentShader;

    GLint               uniformCameraPosition;
    GLint               uniformSize;

    Camera*             camera;

    GLfloat             viewportSize;

    bool                isValueRendering;

    void                initVBO();
    void                initShaderProgram(const std::vector<QString>& vertexShaderFilenames, const std::vector<QString>& fragmentShaderFilenames, QString programName);
    void                initCamera();
    void                initUniforms();
    void                initAttribs();
};

#endif /* TEXTURERENDERER_H_ */
