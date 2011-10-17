#ifndef GEOMETRYSHADER_H_
#define GEOMETRYSHADER_H_

#include "Shader.h"

class GeometryShader : public Shader
{
public:

                /**
                 * Throws exception if compilation or file reading fails.
                 */

                GeometryShader(const std::vector<QString>& filenames, const QString additionalSource = "");
    virtual     ~GeometryShader();
};

#endif /* GEOMETRYSHADER_H_ */
