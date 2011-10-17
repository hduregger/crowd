#ifndef GROUPSTATESRENDERER_H_
#define GROUPSTATESRENDERER_H_

#include "TextureRendererAlpha.h"

class GroupStatesRenderer : public TextureRendererAlpha
{
public:
                    GroupStatesRenderer(GLfloat viewportSize, const Texture* texture0, const Texture* texture1, const std::vector<QString>& vertexShaderFilenames, const std::vector<QString>& fragmentShaderFilenames, QString programName, bool isValueRenderer);
    virtual         ~GroupStatesRenderer();

    void            render(int index);

private:

    const Texture*  texture1;
};

#endif /* GROUPSTATESRENDERER_H_ */
