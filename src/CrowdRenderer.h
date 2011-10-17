#ifndef CROWDRENDERER_H_
#define CROWDRENDERER_H_


#define USE_GPU
#define GL3_PROTOTYPES 1

#include "graphics/gl3.h"

#include "renderers/ComponentValueRenderer.h"
#include "renderers/TextureRenderer.h"
#include "renderers/TextureRendererAlpha.h"
#include "renderers/ValueRenderer.h"
#include "renderers/DirectionRenderer.h"
#include "renderers/GradientRenderer.h"
#include "renderers/AgentsRenderer.h"
#include "renderers/GroupStatesRenderer.h"

#include "graphics/Texture.h"

#include "Agent.h"

#include "States.h"

#include "Settings.h"


class CrowdRenderer
{
public:
                                    CrowdRenderer();
    virtual                         ~CrowdRenderer();

    void                            initializeRenderers(GLfloat                 viewportSize,
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
                                                        const Settings*         settings);

    void                            render( GLfloat positionX,
                                            GLfloat positionY,
                                            GLfloat width,
                                            GLfloat height,
                                            GLuint  count,
                                            const BufferTexture* positions,
                                            const BufferTexture* directions,
                                            const BufferTexture* ids,
                                            const BufferTexture* radii,
                                            GLint   groupStatesIndex);

    void                            setMapAlpha(GLfloat alpha);
    void                            setWorkGroupsAlpha(GLfloat alpha);
    void                            setWorkItemsAlpha(GLfloat alpha);
    void                            setGroupStatesAlpha(GLfloat alpha);
    void                            setGradientArrowsAlpha(GLfloat alpha);

    void                            setGradientFilterState(bool isInterpolating);

    float                           getColorScaleMin();
    void                            setColorScaleMin(float min);
    float                           getColorScaleMax();
    void                            setColorScaleMax(float max);

    void                            setFieldRenderState(FieldRenderState::State state);
    FieldRenderState::State         getFieldRenderState();

    void                            setAgentGroupRenderState(AgentGroupRenderState::State state);
    AgentGroupRenderState::State    getAgentGroupRenderState();

    void                            setDirectionRenderState(DirectionRenderState::State state);
    DirectionRenderState::State     getDirectionRenderState();


    TextureRenderer*                getCurrentRenderer();

    void                            setIsDrawingSprites(bool isDrawingSprites);
    void                            setIsDrawingSplatAreas(bool isDrawingAgents);

    QString                         getTotalBufferSizeMessage(int* const sum);

    void                            setScale(float s);

    void                            setUpdateState(UpdateState::State state);

private:

    TextureRendererAlpha*           mapRenderer;

    ValueRenderer*                  discomfortRenderer;
    ValueRenderer*                  densityRenderer;
    DirectionRenderer*              averageVelocityRenderer;
    ComponentValueRenderer*         speedRenderer;
    ComponentValueRenderer*         costRenderer;
    ComponentValueRenderer*         potentialRenderer;
    GradientRenderer*               gradientRenderer;

    TextureRenderer*                splatAreasRenderer;
    TextureRenderer*                currentRenderer;
    AgentsRenderer*                 agentsRenderer;

    TextureRendererAlpha*           workGroupsRenderer;
    TextureRendererAlpha*           workItemsRenderer;

    GroupStatesRenderer*            groupStatesRenderer;


    AgentGroupRenderState::State    agentGroupRenderState;
    DirectionRenderState::State     directionRenderState;

    FieldRenderState::State         fieldRenderState;

    bool                            isDrawingGroupStates;
    bool                            isDrawingSprites;
    bool                            isDrawingSplatAreas;

    Texture2D*                      directionRendererLegend;
    Texture2D*                      arrow;

    void                            initializeDirectionLegend();
    void                            initializeDirectionArrow();
};

#endif /* CROWDRENDERER_H_ */
