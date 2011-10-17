#ifndef COMPONENTVALUERENDERER_H_
#define COMPONENTVALUERENDERER_H_


#include "ValueRenderer.h"
#include "uniform/UnsignedIntegerUniform.h"


class ComponentValueRenderer : public ValueRenderer
{
public:
                        ComponentValueRenderer( GLfloat                       viewportSize,
                                                const Texture*                valueTexture,
                                                const Texture2D*              legend,
                                                const std::vector<QString>&   vertexShaderFilenames,
                                                const std::vector<QString>&   fragmentShaderFilenames,
                                                QString                       programName,
                                                bool                          isValueRenderer);
    virtual             ~ComponentValueRenderer();


    void                setComponent(GLuint component) const;

private:


    UnsignedIntegerUniform*  uniformComponent;
};

#endif /* COMPONENTVALUERENDERER_H_ */
