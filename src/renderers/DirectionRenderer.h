#ifndef DIRECTIONRENDERER_H_
#define DIRECTIONRENDERER_H_

#include "TextureRenderer.h"


class DirectionRenderer : public TextureRenderer
{
public:
                    DirectionRenderer(GLfloat                     viewportSize,
                                      const Texture*              texture,
                                      const Texture2D*            legend,
                                      const Texture2D*            arrow,
                                      const std::vector<QString>& vertexShaderFilenames,
                                      const std::vector<QString>& fragmentShaderFilenames,
                                      QString                     programName);
    virtual         ~DirectionRenderer();

    virtual void    render();

    void            setScale(float scale);

private:

    const Texture*  legend;
    const Texture*  arrow;

    GLint           uniformScale;


};

#endif /* DIRECTIONRENDERER_H_ */
