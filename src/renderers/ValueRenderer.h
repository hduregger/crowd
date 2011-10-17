#ifndef VALUERENDERER_H_
#define VALUERENDERER_H_

#include "TextureRenderer.h"
#include "uniform/FloatUniform.h"

/**
 * Binds valueTexture and renders with the given shaders to a fullscreen rectangle.
 */

class ValueRenderer : public TextureRenderer
{
public:
                        ValueRenderer(GLfloat                       viewportSize,
                                      const Texture*                valueTexture,
                                      const Texture2D*              legend,
                                      const std::vector<QString>&   vertexShaderFilenames,
                                      const std::vector<QString>&   fragmentShaderFilenames,
                                      QString                       programName,
                                      bool                          isValueRenderer);
    virtual             ~ValueRenderer();

    virtual void        setColorScaleMin(float min);
    virtual void        setColorScaleMax(float max);

    virtual float       getColorScaleMin() const;
    virtual float       getColorScaleMax() const;


    virtual void        render();


private:

    FloatUniform*       uniformColorScaleMin;
    FloatUniform*       uniformColorScaleMax;

    float               colorScaleMin;
    float               colorScaleMax;

    const Texture2D*    legend;
};

#endif /* VALUERENDERER_H_ */
