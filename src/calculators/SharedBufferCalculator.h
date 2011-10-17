#ifndef SHAREDBUFFERCALCULATOR_H_
#define SHAREDBUFFERCALCULATOR_H_

#include <CL/cl.h>

#include <vector>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"

#include "../computation/Program.h"
#include "../Logger.h"
#include "../computation/Profiler.h"
#include "../Vector4.h"

#include "../computation/Context.h"

#include "../graphics/BufferTexture.h"

/**
 * Provides buffers shared between OpenGL and OpenCL based on texture buffers.
 * Also holds a OpenCL program.
 */

class SharedBufferCalculator
{
public:
                        SharedBufferCalculator( const Logger*       logger,
                                                Profiler*           profiler,
                                                const Context*      context,
                                                size_t              threadCount,
                                                size_t              workGroupSize,
                                                size_t              bufferCount,
                                                cl_uint             bufferSideLength,
                                                GLsizeiptr          bufferByteSize,
                                                QString             filename,
                                                GLenum              internalFormat);
    virtual             ~SharedBufferCalculator() = 0;

    virtual int         getTotalBufferSize();

    /**
     * Returns a single value at position of the buffer.
     */

    static Vector4      getValue(GLuint buffer, cl_uint positionX, cl_uint positionY, GLenum internalFormat, size_t bufferSideLength);

protected:

    const Logger*       logger;

    Program*            program;

    const Context*      context;

    size_t              threadCount;
    size_t              workGroupSize;

    cl_uint             bufferSideLength;

    size_t              bufferCount;

    std::vector<cl_mem> sharedTextureBuffers;       // OpenCL handles to the buffers shared with OpenGL

    std::vector<GLuint> textureBuffers;             // OpenGL buffers

    GLsizeiptr          bufferByteSize;

    std::vector<BufferTexture*> textureBufferTextures;      // OpenGL textures that refer to the buffers

    int                 totalBufferSize;

    Profiler*           profiler;

    /**
     * Returns a single value at position of the shared buffer with bufferIndex.
     */

    Vector4             getValueIndexed(size_t bufferIndex, cl_uint positionX, cl_uint positionY);


    const BufferTexture* getBufferTexture(size_t i) const;
    cl_mem              getSharedBuffer(size_t i);

private:


    GLenum              internalFormat;


    void                initBuffersAndTextures();
};

#endif /* SHAREDBUFFERCALCULATOR_H_ */
