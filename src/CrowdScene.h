#ifndef CROWD_H_
#define CROWD_H_

#include <QtGui>
#include <QtOpenGL>
#include <QGraphicsScene>

#include <GL/glx.h>
#include <CL/cl.h>

#include "Logger.h"

#include "graphics/Camera.h"
#include "computation/Profiler.h"
#include "computation/ClientProfile.h"
#include "CrowdRenderer.h"
#include "CrowdCalculator.h"
#include "States.h"
#include "Settings.h"


class Splatterer;



class CrowdScene : public QGraphicsScene
{
	Q_OBJECT

public:

	                    CrowdScene( QGLWidget*   qGLWidget,
	                                Logger*      logger,
	                                QString      applicationName,
	                                Vector4      color);
	virtual             ~CrowdScene();

    void                drawBackground(QPainter* painter, const QRectF& canvasArea);

    QRectF              itemsBoundingRect() const;

    void                initialize(const Settings*  settings,
                                   const Texture2D* valueRendererLegend,
                                   const Texture2D* map);


    QString             getTotalBufferSizeMessage();


public slots:

    void    setOuterLoopCount(int outerLoopCount);

    void    setColorScaleMin(float min);
    void    setColorScaleMax(float max);

    float   getColorScaleMin();
    float   getColorScaleMax();

    void    setFieldRenderState(FieldRenderState::State state);
    void    setAgentGroupRenderState(AgentGroupRenderState::State state);
    void    setDirectionRenderState(DirectionRenderState::State state);
    void    setUpdateState(UpdateState::State state);

    void    setMapAlpha(GLfloat alpha);
    void    setWorkGroupsAlpha(GLfloat alpha);
    void    setWorkItemsAlpha(GLfloat alpha);
    void    setGroupStatesAlpha(GLfloat alpha);
    void    setGradientArrowsAlpha(GLfloat alpha);

    void    setGradientFilterState(bool isInterpolating);

    void    setIsResolvingCollisions(bool isResolvingCollisions);

    /**
     * Position coordinates are with y increasing downwards.
     */

    void    performMousePick(QPointF position);

    float   performMousePickExtremum(QPointF position);

    void    performMousePickMinimum(QPointF position);
    void    performMousePickMaximum(QPointF position);

    void    setCostWeightPathLength(float pathLength);
    void    setCostWeightTime(float time);
    void    setCostWeightDiscomfort(float discomfort);

    void    setMinimumDensity(float density);
    void    setMaximumDensity(float density);

    void    setMaximumSpeed(float speed);

    float   getMinimumDensity();
    float   getMaximumDensity();

    void    setInnerLoopCount(uint count);

    size_t  getViewportSize() const;

    void    setDiscomfortBrushRadius(float radius) const;
    void    setDiscomfortBrushIntensity(float intensity) const;

    void    setMousePaintPosition(QPointF position) const;

    void    setExitMode(cl_int exitMode);

signals:

    void    colorScaleMinChanged(float scaleMin);
    void    colorScaleMaxChanged(float scaleMax);
    void    mousePickValueChanged(QString value);
    void    mousePickMinimumValueChanged(float value);
    void    mousePickMaximumValueChanged(float value);

    void    agentCountsChanged(std::vector<cl_uint> agentCounts);

    void    profilingInfoChanged(QString s);
    void    kernelProfilingInfoChanged(QString s);


protected:

    void    timerEvent(QTimerEvent* event);

private slots:

    void    setScale(float s);
    void    setIsDrawingSprites(bool isDrawingSprites);
    void    setIsDrawingSplatAreas(bool isDrawingAgents);
    void    setIsPlaying(bool isPlaying);
    void    setIsPrintingProfilingInfo(bool isPrinting);
    void    setIsProfilingDetails(bool isProfiling);
    void    setIsBreakingAfterSolverStep(bool isBreakingAfterSolverStep);
    void    performStep();
    void    performRewind();



private:

    /**
     * Position coordinates are with y increasing upwards.
     * If extremum is not NULL, the value of buffers valid for extremum picking
     * will be written to the float pointed to by extremum.
     */

    QString getValueAt(QPointF position, float* extremum = NULL);

    /**
     * Returns a string representing the heading defined by the direction vector.
     * The string is the heading in degrees terminated by the degree symbol.
     * If the direction is the zero vector, "n/a" is returned.
     */

    QString getHeadingString(float x, float y);

    /**
     * Returns the component of v that stands for the current AgentGroupRenderState::State.
     */

    float   getComponentForCurrentGroup(Vector4 v);

    /**
     * Returns the component of v that stands for the current DirectionRenderState::State.
     */

    float   getComponentForCurrentDirection(Vector4 v);

    /**
     * Position coordinates are with y increasing upwards.
     */

    Vector4 getTextureValueAt(QPointF position);

    bool                isInitialized;

    Logger*             logger;

    Display*			displayX11;
    GLXContext			contextGLX;

    QGLWidget*          glWidget;

    float               scale;

    bool                    isPlaying;
    bool                    doStep;

    bool                    isResolvingCollisions;

    bool                    isFirstFrame;


    cl_float                previousTime;

    uint                    agentCount;



    // Profiling

    ClientProfile*                      clientProfile;

    bool                                isPrintingProfilerInfo;
    bool                                isProfilingDetails;

    size_t                              viewportSize;




    QString                             applicationName;

    CrowdRenderer*                      crowdRenderer;
    CrowdCalculator*                    crowdCalculator;

    bool                                isProfilingQueue;

    Profiler*                           profiler;

    Vector4                             color;


    void                    computeAndRender(const QRectF& canvasArea);


    float                   headingFromVector(float x, float y);
    float                   transformToHeading(float angle);

    void                    signalSettings(TextureRenderer* valueRenderer);

};

#endif
