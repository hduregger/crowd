#ifndef AGENTSRENDERER_H_
#define AGENTSRENDERER_H_

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"

#include "../graphics/Camera.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/VertexShader.h"
#include "../graphics/GeometryShader.h"
#include "../graphics/FragmentShader.h"
#include "../graphics/Texture2D.h"
#include "../graphics/BufferTexture.h"

#include "../Settings.h"


class AgentsRenderer
{
public:
                        AgentsRenderer( GLfloat domainSize, const Settings* settings);
    virtual             ~AgentsRenderer();

    void                render(GLuint                  count,
                               const BufferTexture*    positions,
                               const BufferTexture*    directions,
                               const BufferTexture*    ids,
                               const BufferTexture*    radii        ) const;

    int                 getTotalBufferSize();

private:

    GLuint              pointBuffer;       // buffer with single point for instancing

    Texture2D*          agent0;
    Texture2D*          agent1;
    Texture2D*          agent2;
    Texture2D*          agent3;

    GLint               attribVertex;

    ShaderProgram*      shaderProgram;
    VertexShader*       vertexShader;
    GeometryShader*     geometryShader;
    FragmentShader*     fragmentShader;

    Camera*             camera;

    int                 totalBufferSize;

    void                initVBO();
    void                initShaderProgram();
    void                initCamera(GLfloat domainSize);
    void                initUniforms();
    void                initAttribs();

    Texture2D*          initializeAgentTexture(QString textureFilename);
};

#endif /* AGENTSRENDERER_H_ */
