TEMPLATE = app
CONFIG(debug, debug|release):TARGET = crowdd
else:TARGET = crowd
CONFIG(debug, debug|release):DEFINES += DEBUG
else:DEFINES += 
QT += core \
    gui \
    opengl
HEADERS += src/SplashScreen.h \
    src/renderers/uniform/Vec2Uniform.h \
    src/renderers/uniform/UnsignedIntegerUniform.h \
    src/renderers/uniform/Mat4Uniform.h \
    src/renderers/uniform/IntegerUniform.h \
    src/renderers/uniform/FloatUniform.h \
    src/Settings.h \
    src/computation/OpenCL.h \
    src/computation/Profiler.h \
    src/computation/ProfilingElement.h \
    src/computation/Program.h \
    src/computation/ClientProfile.h \
    src/computation/Context.h \
    src/graphics/Texture2DPair.h \
    src/renderers/ComponentValueRenderer.h \
    src/renderers/DirectionRenderer.h \
    src/renderers/GroupStatesRenderer.h \
    src/graphics/TextureBufferTripple.h \
    src/graphics/BufferTexture.h \
    src/Agent.h \
    src/graphics/OpenGL.h \
    src/SystemTime.h \
    src/String.h \
    src/Number.h \
    src/CrowdCalculator.h \
    src/States.h \
    src/CrowdRenderer.h \
    src/renderers/AgentsRenderer.h \
    src/calculators/SpeedCalculator.h \
    src/renderers/GradientRenderer.h \
    src/calculators/CollisionResolver.h \
    src/calculators/AverageVelocityCalculator.h \
    src/calculators/CostCalculator.h \
    src/calculators/Splatterer.h \
    src/graphics/Texture.h \
    src/graphics/Texture2D.h \
    src/Random.h \
    src/calculators/WorkItemCalculator.h \
    src/Application.h \
    src/CrowdScene.h \
    src/Error.h \
    src/Exception.h \
    src/GraphicsView.h \
    src/Logger.h \
    src/MainWindow.h \
    src/Vector4.h \
    src/calculators/AgentMover.h \
    src/calculators/GradientCalculator.h \
    src/calculators/PotentialCalculator.h \
    src/calculators/SharedBufferCalculator.h \
    src/calculators/WorkGroupCalculator.h \
    src/graphics/Camera.h \
    src/graphics/FragmentShader.h \
    src/graphics/GeometryShader.h \
    src/graphics/Shader.h \
    src/graphics/ShaderProgram.h \
    src/graphics/VertexShader.h \
    src/graphics/gl3.h \
    src/renderers/TextureRenderer.h \
    src/renderers/TextureRendererAlpha.h \
    src/renderers/ValueRenderer.h \
    src/renderers/TextureRendererAlpha.h \
    src/renderers/TextureRenderer.h \
    src/renderers/ValueRenderer.h \
    src/Application.h
SOURCES += src/SplashScreen.cpp \
    src/renderers/uniform/Vec2Uniform.cpp \
    src/renderers/uniform/UnsignedIntegerUniform.cpp \
    src/renderers/uniform/Mat4Uniform.cpp \
    src/renderers/uniform/IntegerUniform.cpp \
    src/renderers/uniform/FloatUniform.cpp \
    src/Settings.cpp \
    src/computation/OpenCL.cpp \
    src/computation/Profiler.cpp \
    src/computation/ProfilingElement.cpp \
    src/computation/Program.cpp \
    src/computation/ClientProfile.cpp \
    src/computation/Context.cpp \
    src/graphics/Texture2DPair.cpp \
    src/renderers/ComponentValueRenderer.cpp \
    src/renderers/DirectionRenderer.cpp \
    src/renderers/GroupStatesRenderer.cpp \
    src/graphics/TextureBufferTripple.cpp \
    src/graphics/BufferTexture.cpp \
    src/graphics/OpenGL.cpp \
    src/SystemTime.cpp \
    src/String.cpp \
    src/Number.cpp \
    src/CrowdCalculator.cpp \
    src/CrowdRenderer.cpp \
    src/renderers/AgentsRenderer.cpp \
    src/calculators/SpeedCalculator.cpp \
    src/renderers/GradientRenderer.cpp \
    src/calculators/CollisionResolver.cpp \
    src/Main.cpp \
    src/calculators/AverageVelocityCalculator.cpp \
    src/calculators/CostCalculator.cpp \
    src/calculators/Splatterer.cpp \
    src/graphics/Texture.cpp \
    src/graphics/Texture2D.cpp \
    src/calculators/WorkItemCalculator.cpp \
    src/renderers/TextureRendererAlpha.cpp \
    src/calculators/SharedBufferCalculator.cpp \
    src/calculators/WorkGroupCalculator.cpp \
    src/calculators/AgentMover.cpp \
    src/calculators/GradientCalculator.cpp \
    src/calculators/PotentialCalculator.cpp \
    src/renderers/TextureRenderer.cpp \
    src/renderers/ValueRenderer.cpp \
    src/graphics/Camera.cpp \
    src/Application.cpp \
    src/graphics/ShaderProgram.cpp \
    src/graphics/GeometryShader.cpp \
    src/graphics/FragmentShader.cpp \
    src/graphics/Shader.cpp \
    src/graphics/VertexShader.cpp \
    src/CrowdScene.cpp \
    src/Error.cpp \
    src/Exception.cpp \
    src/GraphicsView.cpp \
    src/Logger.cpp \
    src/MainWindow.cpp
FORMS += crowdqt.ui
RESOURCES += 
LIBS += -L/usr/lib/fglrx \
    -lGL \
    -lGLU \
    -lOpenCL
INCLUDEPATH += /usr/include
QMAKE_CXXFLAGS += -Werror
