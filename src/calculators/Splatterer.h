#ifndef SPLATTERER_H_
#define SPLATTERER_H_

#include <stddef.h>
#include <vector>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"

#include <CL/cl.h>

#include "../Vector4.h"
#include "../Logger.h"
#include "../graphics/Camera.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/VertexShader.h"
#include "../graphics/GeometryShader.h"
#include "../graphics/FragmentShader.h"
#include "../graphics/Texture2D.h"
#include "../graphics/BufferTexture.h"
#include "../graphics/TextureBufferTripple.h"
#include "../renderers/uniform/FloatUniform.h"
#include "../renderers/uniform/Vec2Uniform.h"
#include "../renderers/TextureRenderer.h"



/**
 * Splats the agent density contributions onto the buffer.
 */

class Splatterer
{
public:
                        Splatterer( const Logger*       logger,
                                    const Context*      context,
                                    GLfloat             viewportSize,
                                    QString             textureFilename,
                                    BufferTexture*      baseDiscomfort);
    virtual             ~Splatterer();

    const Texture2D*    getDensitiesDiscomfortsVelocities() const;
    const Texture2D*    getSplatAreas() const;
    const BufferTexture* getAverageVelocities() const;

    void                splat(  GLuint                  count,
                                const BufferTexture*    positions,
                                const BufferTexture*    directions,
                                const BufferTexture*    speeds,
                                const BufferTexture*    ids,
                                const BufferTexture*    radii         );

    int                 getTotalBufferSize();

    void                prepareFramebuffer();
    void                copyDataFromFramebuffer();

    cl_mem              getDensitiesDiscomfortsVelocitiesShared();

    Vector4             getDensityDiscomfortVelocity(cl_uint positionX, cl_uint positionY);

    void                setDiscomfortBrushRadius(float radius) const;
    void                setDiscomfortBrushIntensity(float intensity) const;
    void                setDiscomfortBrushPosition(float x, float y) const;


private:

    GLuint              pointBuffer;           // buffer with single point for instancing
    GLuint              screenSizedQuadBuffer; // 4 points for quad for discomfort writing

    GLuint              framebufferObject;

    Texture2D*          densityDiscomfortVelocity;    // density sum attachment
    Texture2D*          splatAreas;                   // visual agent representation attachment

    Texture2D*          agent;                 // single agent density map

    GLint               splatAttribVertex;

    ShaderProgram*      splatProgram;
    VertexShader*       splatVertexShader;
    GeometryShader*     splatGeometryShader;
    FragmentShader*     splatFragmentShader;

    Camera*             camera;

    GLenum              attachments[3];

    GLfloat             bufferSideLength;

    int                 totalBufferSize;

    TextureBufferTripple* densityDiscomfortVelocityTripple;

    const Logger*       logger;
    const Context*      context;

    TextureRenderer*    prepareFramebufferRenderer;

    ShaderProgram*      discomfortProgram;
    VertexShader*       discomfortVertexShader;
    GeometryShader*     discomfortGeometryShader;
    FragmentShader*     discomfortFragmentShader;

    FloatUniform*       discomfortFactor;
    FloatUniform*       discomfortRadius;
    Vec2Uniform*        discomfortPosition;

    void                initVBO();
    void                initSplatShaderProgram();
    void                initDiscomfortShaderProgram();
    void                initCamera();
    void                initUniforms();
    void                initAttribs();
    void                initFramebufferObject();
};

#endif /* SPLATTERER_H_ */
