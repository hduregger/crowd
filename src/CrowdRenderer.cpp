#include "CrowdRenderer.h"

#include "graphics/OpenGL.h"

#include "String.h"


CrowdRenderer::CrowdRenderer()
:   mapRenderer(NULL),
    discomfortRenderer(NULL),
    densityRenderer(NULL),
    averageVelocityRenderer(NULL),
    speedRenderer(NULL),
    costRenderer(NULL),
    potentialRenderer(NULL),
    gradientRenderer(NULL),
    splatAreasRenderer(NULL),
    currentRenderer(NULL),
    agentsRenderer(NULL),
    workGroupsRenderer(NULL),
    workItemsRenderer(NULL),
    groupStatesRenderer(NULL),
    agentGroupRenderState(AgentGroupRenderState::GROUP0),
    directionRenderState(DirectionRenderState::NORTH),
    isDrawingGroupStates(false),
    isDrawingSprites(true),
    isDrawingSplatAreas(false),
    directionRendererLegend(NULL),
    arrow(NULL)
{
}


CrowdRenderer::~CrowdRenderer()
{
    delete discomfortRenderer;
    delete densityRenderer;
    delete potentialRenderer;
    delete workGroupsRenderer;
    delete workItemsRenderer;
    delete gradientRenderer;
    delete splatAreasRenderer;
    delete costRenderer;
    delete averageVelocityRenderer;
    delete speedRenderer;
    delete mapRenderer;
    delete groupStatesRenderer;

    delete agentsRenderer;

    delete arrow;
    delete directionRendererLegend;

}


void CrowdRenderer::initializeDirectionLegend()
{
    try
    {
        QImage image = Texture::loadTexture("textures/directionLegend.png", false, true);

        uint pixelCount = image.width() * image.height();

        std::vector<float> data(pixelCount * 4);

        Texture::convertToFloats(image, data, pixelCount);

        directionRendererLegend = new Texture2D(image.width(), image.height(), GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR, GL_RGBA, GL_RGBA, GL_FLOAT, &data[0]);
    }
    catch (Exception& e)
    {
        throw Exception("Could not load direction legend texture: " + e.message);
    }
}


void CrowdRenderer::initializeDirectionArrow()
{
    try
    {
        QImage image = Texture::loadTexture("textures/directionArrow.png", false, true);

        uint pixelCount = image.width() * image.height();

        std::vector<float> data(pixelCount * 4);

        Texture::convertToFloats(image, data, pixelCount);

        arrow = new Texture2D(image.width(), image.height(), GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGBA, GL_RGBA, GL_FLOAT, &data[0]);
    }
    catch (Exception& e)
    {
        throw Exception("Could not load arrow texture: " + e.message);
    }
}


void CrowdRenderer::initializeRenderers(GLfloat                 viewportSize,
                                        const Texture2D*        valueRendererLegend,
                                        const Texture2D*        map,
                                        const BufferTexture*    cost,
                                        const BufferTexture*    speed,
                                        const Texture2D*        densityDiscomfortVelocity,
                                        const BufferTexture*    averageVelocities,
                                        const BufferTexture*    potential,
                                        const Texture2D*        gradient01,
                                        const Texture2D*        gradient23,
                                        const Texture2D*        splatAreas,
                                        const BufferTexture*    workGroups,
                                        const BufferTexture*    workItems,
                                        const BufferTexture*    groupStates0,
                                        const BufferTexture*    groupStates1,
                                        size_t                  workGroupsPerSide,
                                        const Settings*         settings)
{
    initializeDirectionLegend();
    initializeDirectionArrow();


    std::vector<QString> filenamesVert;
    std::vector<QString> filenamesFragDiscomfort;
    std::vector<QString> filenamesFragDensity;
    std::vector<QString> filenamesFragPotential;
    std::vector<QString> filenamesFragGradient;
    std::vector<QString> filenamesFragAverageVelocity;
    std::vector<QString> filenamesFragSpeed;
    std::vector<QString> filenamesFragWorkGroups;
    std::vector<QString> filenamesFragWorkItems;
    std::vector<QString> filenamesFragCost;
    std::vector<QString> filenamesFragMap;
    std::vector<QString> filenamesFragSplatAreas;
    std::vector<QString> filenamesFragGroupStates;

    filenamesVert.push_back("src/shaders/shared.vert");


    filenamesFragDiscomfort.push_back("src/shaders/shared.frag");
    filenamesFragDensity.push_back("src/shaders/shared.frag");
    filenamesFragPotential.push_back("src/shaders/shared.frag");
    filenamesFragGradient.push_back("src/shaders/shared.frag");
    filenamesFragWorkGroups.push_back("src/shaders/shared.frag");
    filenamesFragWorkItems.push_back("src/shaders/shared.frag");
    filenamesFragCost.push_back("src/shaders/shared.frag");
    filenamesFragAverageVelocity.push_back("src/shaders/shared.frag");
    filenamesFragSpeed.push_back("src/shaders/shared.frag");
    filenamesFragMap.push_back("src/shaders/shared.frag");
    filenamesFragSplatAreas.push_back("src/shaders/shared.frag");
    filenamesFragGroupStates.push_back("src/shaders/shared.frag");

    filenamesFragDiscomfort.push_back("src/shaders/discomfort.frag");
    filenamesFragDensity.push_back("src/shaders/density.frag");
    filenamesFragPotential.push_back("src/shaders/potential.frag");
    filenamesFragGradient.push_back("src/shaders/gradient.frag");
    filenamesFragWorkGroups.push_back("src/shaders/workGroups.frag");
    filenamesFragWorkItems.push_back("src/shaders/workItems.frag");
    filenamesFragCost.push_back("src/shaders/cost.frag");
    filenamesFragAverageVelocity.push_back("src/shaders/averageVelocity.frag");
    filenamesFragSpeed.push_back("src/shaders/speed.frag");
    filenamesFragMap.push_back("src/shaders/map.frag");
    filenamesFragSplatAreas.push_back("src/shaders/splatAreas.frag");
    filenamesFragGroupStates.push_back("src/shaders/groupStates.frag");

    mapRenderer             = new TextureRendererAlpha(viewportSize, map, filenamesVert, filenamesFragMap, "Map Shader", true);

    discomfortRenderer      = new ValueRenderer(viewportSize, densityDiscomfortVelocity, valueRendererLegend, filenamesVert, filenamesFragDiscomfort, "Discomfort Shader", true);
    densityRenderer         = new ValueRenderer(viewportSize, densityDiscomfortVelocity, valueRendererLegend, filenamesVert, filenamesFragDensity, "Density Shader", true);
    averageVelocityRenderer = new DirectionRenderer(viewportSize, averageVelocities, directionRendererLegend, arrow, filenamesVert, filenamesFragAverageVelocity, "Average Velocity Shader");
    speedRenderer           = new ComponentValueRenderer(viewportSize, speed, valueRendererLegend, filenamesVert, filenamesFragSpeed, "Speed Shader", true);
    costRenderer            = new ComponentValueRenderer(viewportSize, cost, valueRendererLegend, filenamesVert, filenamesFragCost, "Cost Shader", true);
    potentialRenderer       = new ComponentValueRenderer(viewportSize, potential, valueRendererLegend, filenamesVert, filenamesFragPotential, "Potential Shader", true);
    gradientRenderer        = new GradientRenderer(viewportSize, gradient01, gradient23, directionRendererLegend, arrow, filenamesVert, filenamesFragGradient, "Gradient Shader");

    splatAreasRenderer      = new TextureRenderer(viewportSize, splatAreas, filenamesVert, filenamesFragSplatAreas, "Splat Areas Shader", true);

    workGroupsRenderer      = new TextureRendererAlpha(viewportSize, workGroups, filenamesVert, filenamesFragWorkGroups, "WorkGroups Shader", true);
    workItemsRenderer       = new TextureRendererAlpha(viewportSize, workItems, filenamesVert, filenamesFragWorkItems, "WorkItems Shader", true);

    groupStatesRenderer     = new GroupStatesRenderer(workGroupsPerSide, groupStates0, groupStates1, filenamesVert, filenamesFragGroupStates, "Group Convergence Shader", true);

    currentRenderer = densityRenderer;

    agentsRenderer = new AgentsRenderer(viewportSize, settings);
}


void CrowdRenderer::render( GLfloat positionX,
                            GLfloat positionY,
                            GLfloat width,
                            GLfloat height,
                            GLuint  count,
                            const BufferTexture* positions,
                            const BufferTexture* directions,
                            const BufferTexture* ids,
                            const BufferTexture* radii,
                            GLint   groupStatesIndex)
{
    //
    // Set viewport
    //

    glViewport(positionX, positionY, width, height );
    GL_ERROR;

    //
    // Render buffers to screen
    //

    currentRenderer->render();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_BLEND);
    GL_ERROR;

    mapRenderer->render();

    if (isDrawingGroupStates)
    {
        groupStatesRenderer->render(groupStatesIndex);
    }

    workGroupsRenderer->render();
    workItemsRenderer->render();

    if (isDrawingSplatAreas)
    {
        splatAreasRenderer->render();
    }

    if (isDrawingSprites)
    {
        agentsRenderer->render(count, positions, directions, ids, radii);
    }

    glDisable(GL_BLEND);
    GL_ERROR;
}


void CrowdRenderer::setFieldRenderState(FieldRenderState::State state)
{
    fieldRenderState = state;

    switch (fieldRenderState)
    {
        case FieldRenderState::DISCOMFORT:
        {
            currentRenderer = discomfortRenderer;

            break;
        }

        case FieldRenderState::DENSITY:
        {
            currentRenderer = densityRenderer;

            break;
        }

        case FieldRenderState::AVERAGE_VELOCITY:
        {
            currentRenderer = averageVelocityRenderer;

            break;
        }

        case FieldRenderState::SPEED:
        {
            currentRenderer = speedRenderer;

            break;
        }

        case FieldRenderState::COST:
        {
            currentRenderer = costRenderer;

            break;
        }

        case FieldRenderState::POTENTIAL:
        {
            currentRenderer = potentialRenderer;

            break;
        }

        case FieldRenderState::GRADIENT:
        {
            currentRenderer = gradientRenderer;

            break;
        }

        default:
        {
            throw Exception("Invalid render state set in CrowdScene");

            break;
        }
    }

}


FieldRenderState::State CrowdRenderer::getFieldRenderState()
{
    return fieldRenderState;
}


TextureRenderer* CrowdRenderer::getCurrentRenderer()
{
    return currentRenderer;
}


void CrowdRenderer::setMapAlpha(GLfloat alpha)
{
    mapRenderer->setAlpha(alpha);
}


void CrowdRenderer::setWorkGroupsAlpha(GLfloat alpha)
{
    workGroupsRenderer->setAlpha(alpha);
}


void CrowdRenderer::setWorkItemsAlpha(GLfloat alpha)
{
    workItemsRenderer->setAlpha(alpha);
}


void CrowdRenderer::setGroupStatesAlpha(GLfloat alpha)
{
    groupStatesRenderer->setAlpha(alpha);
}


void CrowdRenderer::setGradientArrowsAlpha(GLfloat alpha)
{
    gradientRenderer->setAlpha(alpha);
}


void CrowdRenderer::setGradientFilterState(bool isInterpolating)
{
    gradientRenderer->setIsInterpolating(isInterpolating);
}


float CrowdRenderer::getColorScaleMin()
{
    return currentRenderer->getColorScaleMin();
}


void CrowdRenderer::setColorScaleMin(float min)
{
    currentRenderer->setColorScaleMin(min);
}


float CrowdRenderer::getColorScaleMax()
{
    return currentRenderer->getColorScaleMax();
}

void CrowdRenderer::setColorScaleMax(float max)
{
    currentRenderer->setColorScaleMax(max);
}


void CrowdRenderer::setAgentGroupRenderState(AgentGroupRenderState::State state)
{
    potentialRenderer->setComponent(static_cast<GLuint> (state));
    gradientRenderer->setComponent(static_cast<GLuint> (state));

    agentGroupRenderState = state;
}


AgentGroupRenderState::State CrowdRenderer::getAgentGroupRenderState()
{
    return agentGroupRenderState;
}


void CrowdRenderer::setDirectionRenderState(DirectionRenderState::State state)
{
    speedRenderer->setComponent(static_cast<GLuint> (state));
    costRenderer->setComponent(static_cast<GLuint> (state));

    directionRenderState = state;
}


DirectionRenderState::State CrowdRenderer::getDirectionRenderState()
{
    return directionRenderState;
}


void CrowdRenderer::setIsDrawingSprites(bool isDrawingSprites)
{
    this->isDrawingSprites = isDrawingSprites;
}


void CrowdRenderer::setIsDrawingSplatAreas(bool isDrawingSplatAreas)
{
    this->isDrawingSplatAreas = isDrawingSplatAreas;
}


void CrowdRenderer::setScale(float s)
{
    averageVelocityRenderer->setScale(s);
    gradientRenderer->setScale(s);
}


void CrowdRenderer::setUpdateState(UpdateState::State state)
{
    isDrawingGroupStates = state == UpdateState::SELECTIVELY;
}


QString CrowdRenderer::getTotalBufferSizeMessage(int* const sum)
{
    QString message;
    int size;

#define PROCESS_RENDERER(RENDERER, NAME) \
{ \
    size = RENDERER->getTotalBufferSize(); \
    *sum += size; \
    message += String::formatMemoryString(NAME, size) + "\n"; \
}


    PROCESS_RENDERER(discomfortRenderer, "Discomfort Renderer ");
    PROCESS_RENDERER(densityRenderer, "Density Renderer ");
    PROCESS_RENDERER(potentialRenderer, "Potential Renderer ");
    PROCESS_RENDERER(workGroupsRenderer, "Work Groups Renderer ");
    PROCESS_RENDERER(workItemsRenderer, "Work Items Renderer ");
    PROCESS_RENDERER(gradientRenderer, "Gradient Renderer ");
    PROCESS_RENDERER(splatAreasRenderer, "Splat Areas Renderer ");
    PROCESS_RENDERER(costRenderer, "Cost Renderer ");
    PROCESS_RENDERER(averageVelocityRenderer, "Average Velocity Renderer ");
    PROCESS_RENDERER(speedRenderer, "Speed Renderer ");
    PROCESS_RENDERER(mapRenderer, "Map Renderer ");
    PROCESS_RENDERER(groupStatesRenderer, "Group States Renderer ");
    PROCESS_RENDERER(agentsRenderer, "Agents Renderer ");

    return message;
}
