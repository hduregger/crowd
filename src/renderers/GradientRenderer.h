#ifndef GRADIENTRENDERER_H_
#define GRADIENTRENDERER_H_

#include "DirectionRenderer.h"

#include "uniform/FloatUniform.h"
#include "uniform/UnsignedIntegerUniform.h"


class GradientRenderer : public DirectionRenderer
{
public:
                            GradientRenderer(   GLfloat                     viewportSize,
                                                const Texture2D*            gradientTexture01,
                                                const Texture2D*            gradientTexture23,
                                                const Texture2D*            legend,
                                                const Texture2D*            arrow,
                                                const std::vector<QString>& vertexShaderFilenames,
                                                const std::vector<QString>& fragmentShaderFilenames,
                                                QString                     programName);
    virtual                 ~GradientRenderer();

    void                    setComponent(GLuint component) const;
    void                    setAlpha(GLfloat alpha) const;

    void                    setIsInterpolating(bool isInterpolating);

    virtual void            render();

private:

    const Texture2D*        gradientTexture23;

    UnsignedIntegerUniform* component;
    UnsignedIntegerUniform* pass;

    FloatUniform*           alpha;

    bool                    isInterpolating;
};

#endif /* GRADIENTRENDERER_H_ */
