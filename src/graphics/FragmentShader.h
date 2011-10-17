#ifndef FRAGMENTSHADER_H_
#define FRAGMENTSHADER_H_

#include "Shader.h"

class FragmentShader : public Shader
{
public:
                /**
                 * Throws exception if compilation or file reading fails.
                 */

                FragmentShader(const std::vector<QString>& filenames, const QString additionalSource = "");
    virtual     ~FragmentShader();
};

#endif /* FRAGMENTSHADER_H_ */
