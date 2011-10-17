#ifndef VERTEXSHADER_H_
#define VERTEXSHADER_H_

#include "Shader.h"

class VertexShader : public Shader
{
public:
                /**
                 * Throws exception if compilation or file reading fails.
                 */

                VertexShader(const std::vector<QString>& filenames, const QString additionalSource = "");
    virtual     ~VertexShader();
};

#endif /* VERTEXSHADER_H_ */
