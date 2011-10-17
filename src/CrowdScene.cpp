#include <QImage>

#define GL3_PROTOTYPES 1

#include "graphics/gl3.h"

#include "Application.h"
#include "CrowdScene.h"
#include "Error.h"
#include "Exception.h"
#include "graphics/OpenGL.h"
#include "computation/OpenCL.h"
#include "Number.h"
#include "String.h"
#include "SystemTime.h"
#include "Random.h"

#include <CL/cl.h>
#include <CL/cl_gl.h>

#include <GL/glu.h>

#include <math.h>
#include <stddef.h>
#include <time.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;


CrowdScene::CrowdScene(QGLWidget*   qGLWidget,
                       Logger*      logger,
                       QString      applicationName,
                       Vector4      color)
:   isInitialized(false),
    logger(logger),
    displayX11(NULL),
    contextGLX(0),
    glWidget(qGLWidget),
    scale(1.0f),
    isPlaying(true),
    isResolvingCollisions(true),
    isFirstFrame(true),
    previousTime(0.0f),
    agentCount(agentCount),
    clientProfile(NULL),
    isPrintingProfilerInfo(false),
    isProfilingDetails(false),
    viewportSize(0),
    applicationName(applicationName),
    crowdRenderer(NULL),
    crowdCalculator(NULL),
    isProfilingQueue(false),
    profiler(NULL),
    color(color)
{
}


CrowdScene::~CrowdScene()
{
    delete clientProfile;

    delete crowdRenderer;
    delete crowdCalculator;

    delete profiler;
}





// Note: does get called twice if Qt throws GL error
//       does print error twice if exception is thrown
//       drawbackground is called twice in some cases
//       maybe related to http://bugreports.qt.nokia.com/browse/QTBUG-14559

void CrowdScene::computeAndRender(const QRectF& canvasArea)
{
    try
    {
        if (isPrintingProfilerInfo)
        {
            clientProfile->start( &clientProfile->computationAndRenderTime );
        }

        //
        // Compute viewport position
        //

        float rectX = canvasArea.x();
        float rectY = canvasArea.y();

//            logger->logInfo("Rect: " + QString::number(rectX) + ":" + QString::number(rectY) + " " + QString::number(rect.width()) + ":" + QString::number(rect.height()));

        float px = rectX;
        float py = rectY;

        px = -rectX;
        py = -height() + canvasArea.height() + rectY;


        cl_float deltaTime = 0.00000000001f;

        if (isFirstFrame)
        {
            previousTime = SystemTime::getTimeSeconds();
        }

        if (isPlaying || doStep || isFirstFrame)
        {
            // Note: using fixed time step for now since we never get below this threshold anyway

            deltaTime = 1.0f/33.0f;

//            deltaTime = SystemTime::getTimeSeconds() - previousTime;
//
//            cl_float t = 1.0f/33.0f;
//
//            if (deltaTime > t)
//            {
//                deltaTime = t;
//            }
        }

        //
        // Computation and rendering
        //

        glPushClientAttrib( GL_CLIENT_ALL_ATTRIB_BITS );
        glPushAttrib( GL_ALL_ATTRIB_BITS );
        {
            if (isPlaying || doStep || isFirstFrame)
            {
                crowdCalculator->compute(clientProfile, isPrintingProfilerInfo && isProfilingDetails, isResolvingCollisions, deltaTime);
            }

            if (isPrintingProfilerInfo)
            {
                glFinish();
                clientProfile->start( &clientProfile->renderTime );
            }

            //
            // Clear canvas to background color
            //

            glClearColor(color.x, color.y, color.z, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            GL_ERROR;

            crowdRenderer->render(  px * scale,
                                    py * scale,
                                    static_cast<float> (width() * scale),
                                    static_cast<float> (height() * scale),
                                    agentCount,
                                    crowdCalculator->getPositions(),
                                    crowdCalculator->getDirections(),
                                    crowdCalculator->getIds(),
                                    crowdCalculator->getRadii(),
                                    crowdCalculator->getGroupStatesReadIndex());

            std::vector<cl_uint> agentCounts = crowdCalculator->getAgentCounts();
            emit agentCountsChanged(agentCounts);

            if (isPrintingProfilerInfo)
            {
                glFinish();
                clientProfile->stop( &clientProfile->renderTime );
            }
        }
        glPopAttrib();
        glPopClientAttrib();

        if (isPrintingProfilerInfo)
        {
            clientProfile->stop( &clientProfile->computationAndRenderTime );
        }

        doStep = false;
        isFirstFrame = false;

        GL_ERROR;
    }
    catch (Exception& e)
    {
        logger->logError("An error occurred during computing or painting:\n  " + e.message);

        Application::exit(1);
    }
    catch (std::exception& e)
    {
        logger->logError("An error occurred during computing or painting:\n  " + QString(e.what()));

        Application::exit(1);
    }
    catch (...)
    {
        logger->logError("An error occurred during computing or painting.");

        Application::exit(1);
    }
}


void CrowdScene::setFieldRenderState(FieldRenderState::State state)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setFieldRenderState(state);

        signalSettings(crowdRenderer->getCurrentRenderer());
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting field render state:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setMapAlpha(GLfloat alpha)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setMapAlpha(alpha);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting alpha of map renderer:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setWorkGroupsAlpha(GLfloat alpha)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setWorkGroupsAlpha(alpha);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting alpha of work groups renderer:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setWorkItemsAlpha(GLfloat alpha)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setWorkItemsAlpha(alpha);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting alpha of work items renderer:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setGroupStatesAlpha(GLfloat alpha)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setGroupStatesAlpha(alpha);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting alpha of group states renderer:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setGradientArrowsAlpha(GLfloat alpha)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setGradientArrowsAlpha(alpha);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting alpha of gradient arrows renderer:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setGradientFilterState(bool isInterpolating)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setGradientFilterState(isInterpolating);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting gradient filter state:\n  " + e.message);

        Application::exit(1);
    }
}



void CrowdScene::setIsResolvingCollisions(bool isResolvingCollisions)
{
    try
    {
        glWidget->makeCurrent();

        this->isResolvingCollisions = isResolvingCollisions;
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting collusion resolution state:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setMousePaintPosition(QPointF position) const
{
    try
    {
        glWidget->makeCurrent();

        // Flip y direction
        // weird, -1 should be correct, must be something else somewhere

        position.setY(viewportSize - position.y());// - 1);

        crowdCalculator->setDiscomfortBrushPosition(position.x(), position.y());
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting mouse paint position:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::performMousePick(QPointF position)
{
    try
    {
        glWidget->makeCurrent();

        // Flip y direction
        // weird, -1 should be correct, must be something else somewhere

        position.setY(viewportSize - position.y());// - 1);

        QString value = getValueAt(position);

        emit mousePickValueChanged(value);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while picking with mouse:\n  " + e.message);

        Application::exit(1);
    }
}


float CrowdScene::performMousePickExtremum(QPointF position)
{
    glWidget->makeCurrent();

    // Flip y direction
    // weird, -1 should be correct, must be something else somewhere

    position.setY(viewportSize - position.y());// - 1);

    QPoint p(position.x(), position.y());

    float extremum;

    getValueAt(position, &extremum);

    return extremum;
}


void CrowdScene::performMousePickMinimum(QPointF position)
{
    try
    {
        float value = performMousePickExtremum(position);

        if (value < getColorScaleMax())
        {
            emit mousePickMinimumValueChanged(value);
        }
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while picking with mouse:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::performMousePickMaximum(QPointF position)
{
    try
    {
        float value = performMousePickExtremum(position);

        if (value > getColorScaleMin())
        {
            emit mousePickMaximumValueChanged(value);
        }
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while picking with mouse:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setOuterLoopCount(int outerLoopCount)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setOuterLoopCount(outerLoopCount);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting outer loop count:\n  " + e.message);

        Application::exit(1);
    }
}


float CrowdScene::getColorScaleMin()
{
    float min = 0.0f;

    try
    {
        glWidget->makeCurrent();

        min = crowdRenderer->getColorScaleMin();
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while getting color scale min:\n  " + e.message);

        Application::exit(1);
    }

    return min;
}


void CrowdScene::setColorScaleMin(float min)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setColorScaleMin(min);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting color scale min:\n  " + e.message);

        Application::exit(1);
    }
}


float CrowdScene::getColorScaleMax()
{
    float max = 0.0f;

    try
    {
        glWidget->makeCurrent();

        max = crowdRenderer->getColorScaleMax();
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting color scale max:\n  " + e.message);

        Application::exit(1);
    }

    return max;
}


void CrowdScene::setColorScaleMax(float max)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setColorScaleMax(max);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting color scale max:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setScale(float s)
{
    try
    {
        glWidget->makeCurrent();

        scale = s;

        crowdRenderer->setScale(s);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting scale:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setIsDrawingSprites(bool isDrawingSprites)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setIsDrawingSprites(isDrawingSprites);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting sprite drawing state state:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setIsDrawingSplatAreas(bool isDrawingSplatAreas)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setIsDrawingSplatAreas(isDrawingSplatAreas);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting splat areas rendering state:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setIsPlaying(bool isPlaying)
{
    this->isPlaying = isPlaying;
}


void CrowdScene::setIsPrintingProfilingInfo(bool isPrinting)
{
    this->isPrintingProfilerInfo = isPrinting;

    if (isPrinting)
    {
        clientProfile->clear();
    }
}


void CrowdScene::setIsProfilingDetails(bool isProfiling)
{
    this->isProfilingDetails = isProfiling;
}


void CrowdScene::setIsBreakingAfterSolverStep(bool isBreakingAfterSolverStep)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setIsBreakingAfterOuterStep(isBreakingAfterSolverStep);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting breaking after step state:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::performStep()
{
    doStep = true;
}


void CrowdScene::performRewind()
{
    crowdCalculator->rewind();
}


void CrowdScene::signalSettings(TextureRenderer* renderer)
{
    emit colorScaleMinChanged(renderer->getColorScaleMin());
    emit colorScaleMaxChanged(renderer->getColorScaleMax());
}


void CrowdScene::setCostWeightPathLength(float pathLength)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setCostWeightPathLength(pathLength);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting length weight:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setCostWeightTime(float time)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setCostWeightTime(time);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting time weight:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setCostWeightDiscomfort(float discomfort)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setCostWeightDiscomfort(discomfort);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting discomfort weight:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setAgentGroupRenderState(AgentGroupRenderState::State state)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setAgentGroupRenderState(state);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting group render state:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setDirectionRenderState(DirectionRenderState::State state)
{
    try
    {
        glWidget->makeCurrent();

        crowdRenderer->setDirectionRenderState(state);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting direction render state:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setUpdateState(UpdateState::State state)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setUpdateState(state);
        crowdRenderer->setUpdateState(state);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting direction render state:\n  " + e.message);

        Application::exit(1);
    }
}



void CrowdScene::setExitMode(cl_int exitMode)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setExitMode(exitMode);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting exit mode:\n  " + e.message);

        Application::exit(1);
    }
}



void CrowdScene::timerEvent(QTimerEvent*)
{
    update();
}

/**
 * Computes angle from normalized direction.
 * y only gives quadrant (need not be normalized).
 */

float CrowdScene::headingFromVector(float x, float y)
{
    static const float RAD_TO_DEG = 360.0f / (2.0f * M_PI);

    float angle = acos(x);

    if (y < 0.0f)
    {
        angle = -angle;
    }

    angle *= RAD_TO_DEG;

    angle = transformToHeading(angle);

    return angle;
}


float CrowdScene::transformToHeading(float angle)
{
    if (angle > 0.0f)
    {
        angle = 180.0f + 180.0f - angle;
    }

    angle = fabs(angle);

    angle += 90.0f;


    if (angle >= 360.0f)
    {
        angle = angle - 360.0f;
    }

    return angle;
}


float CrowdScene::getComponentForCurrentGroup(Vector4 v)
{
    float f;

    switch (crowdRenderer->getAgentGroupRenderState())
    {
        case AgentGroupRenderState::GROUP0:
        {
            f = v.x;
            break;
        }

        case AgentGroupRenderState::GROUP1:
        {
            f = v.y;
            break;
        }

        case AgentGroupRenderState::GROUP2:
        {
            f = v.z;
            break;
        }

        case AgentGroupRenderState::GROUP3:
        {
            f = v.w;
            break;
        }

        default:
        {
            throw Exception("Invalid agent group state for picking");
            break;
        }
    }

    return f;
}


float CrowdScene::getComponentForCurrentDirection(Vector4 v)
{
    float f;

    switch (crowdRenderer->getDirectionRenderState())
    {
        case DirectionRenderState::NORTH:
        {
            f = v.x;
            break;
        }

        case DirectionRenderState::EAST:
        {
            f = v.y;
            break;
        }

        case DirectionRenderState::SOUTH:
        {
            f = v.z;
            break;
        }

        case DirectionRenderState::WEST:
        {
            f = v.w;
            break;
        }

        default:
        {
            throw Exception("Invalid direction state for picking");
            break;
        }
    }

    return f;
}


QString CrowdScene::getHeadingString(float x, float y)
{
    QString s;

// logger->logInfo(QString::number(x) + " " + QString::number(y));

    float l = NumberTemplate<float>::length(x, y);

    if ( ((x == 0.0f) && (y == 0.0f)) || isnan(x) || isnan(y) )
    {
        s = "n/a";
    }
    else if (isinf(x) || isinf(y))
    {
        if (isinf(x) && (x > 0.0f))
        {
            if (isinf(y) && (y > 0.0f))
            {
                s = "45.0" + String::degree();
            }
            else if (isinf(y) && (y < 0.0f))
            {
                s = "135.0" + String::degree();
            }
            else
            {
                s = "90.0" + String::degree();
            }
        }
        else if (isinf(x) && (x < 0.0f))
        {
            if (isinf(y) && (y > 0.0f))
            {
                s = "315.0" + String::degree();
            }
            else if (isinf(y) && (y < 0.0f))
            {
                s = "225.0" + String::degree();
            }
            else
            {
                s = "270.0" + String::degree();
            }
        }
        else
        {
            if (isinf(y) && (y > 0.0f))
            {
                s = "0.0" + String::degree();
            }
            else if (isinf(y) && (y < 0.0f))
            {
                s = "180.0" + String::degree();
            }
        }
    }
    else
    {
        // We only need to normalize the x coordinates

        x /= l;

        float angle = headingFromVector(x, y);

        s = QString::number(angle) + String::degree();
    }

    return s;
}


QString CrowdScene::getValueAt(QPointF position, float* extremum)
{
    QString value;

    try
    {
        glWidget->makeCurrent();

        QPoint p(position.x(), position.y());

        // If inside the domain

        if ( (position.x() >= 0.0f) && (position.x() < viewportSize) &&
             (position.y() >= 0.0f) && (position.y() < viewportSize)    )
        {
            switch (crowdRenderer->getFieldRenderState())
            {
                case FieldRenderState::DISCOMFORT:
                {
                    // y is discomfort

                    float f = crowdCalculator->getDensityDiscomfortVelocity(p.x(), p.y()).y;

                    value = QString::number(f);

                    if (extremum != NULL)
                    {
                        *extremum = f;
                    }

                    break;
                }

                case FieldRenderState::DENSITY:
                {
                    // x is density sum

                    float density = crowdCalculator->getDensityDiscomfortVelocity(p.x(), p.y()).x;

                    value = QString::number(density);

                    if (extremum != NULL)
                    {
                        *extremum = density;
                    }

                    break;
                }

                case FieldRenderState::AVERAGE_VELOCITY:
                {
                    Vector4 v = crowdCalculator->getDensityDiscomfortVelocity(p.x(), p.y());

                    value = getHeadingString(v.z, v.w);

                    break;
                }


                case FieldRenderState::SPEED:
                {
                    Vector4 v = crowdCalculator->getSpeed(p.x(), p.y());

                    float f = getComponentForCurrentDirection(v);

                    value = QString::number(f);

                    if (extremum != NULL)
                    {
                        *extremum = f;
                    }

                    break;
                }

                case FieldRenderState::COST:
                {
                    Vector4 v = crowdCalculator->getCost(p.x(), p.y());

                    float f = getComponentForCurrentDirection(v);

                    value = QString::number(f);

                    if (extremum != NULL)
                    {
                        *extremum = f;
                    }

                    break;
                }


                case FieldRenderState::POTENTIAL:
                {
                    Vector4 v = crowdCalculator->getPotential(p.x(), p.y());

                    float f = getComponentForCurrentGroup(v);

                    value = QString::number(f);

                    if (extremum != NULL)
                    {
                        *extremum = f;
                    }

                    break;
                }


                case FieldRenderState::GRADIENT:
                {
                    float x;
                    float y;

                    crowdCalculator->getGradient(p.x(), p.y(), crowdRenderer->getAgentGroupRenderState(), &x, &y);

                    value = getHeadingString(x, y);

                    break;
                }

                default:
                {
                    throw Exception("Invalid field render state");
                    break;
                }
            }
        }
        else
        {
            value = "n/a";

            if (extremum != NULL)
            {
                *extremum = 0.0f;
            }
        }

    }
    catch (Exception e)
    {
        logger->logError("An error occurred while getting value at:\n  " + e.message);

        Application::exit(1);
    }

    return value;
}





void CrowdScene::initialize(const Settings*  settings,
                            const Texture2D* valueRendererLegend,
                            const Texture2D* map)
{
    try
    {
        profiler = new Profiler();

        isProfilingQueue = settings->isProfilingQueue;

        agentCount = settings->agentCount;

        glWidget->makeCurrent();

        displayX11 = glXGetCurrentDisplay();

        if (displayX11 == NULL)
        {
            throw Exception("Could not access X display");
        }

        contextGLX = glXGetCurrentContext();

        if (contextGLX == NULL)
        {
            throw Exception("Could not access GLX context");
        }


        clientProfile = new ClientProfile(10);

        crowdCalculator = new CrowdCalculator(  logger,
                                                profiler,
                                                displayX11,
                                                contextGLX,
                                                settings);

        size_t bufferSideLength    = crowdCalculator->getBufferSideLength();
        size_t workGroupSideLength = crowdCalculator->getWorkGroupSideLength();

        QString domainSize          = "(" + QString::number(bufferSideLength) + ", "    + QString::number(bufferSideLength) + ")";
        QString workGroupSizeString = "(" + QString::number(workGroupSideLength) + ", " + QString::number(workGroupSideLength) + ")";

        logger->logInfo("Domain size is " + domainSize + "." );
        logger->logInfo("Work group size is " + workGroupSizeString + "." );

        viewportSize = bufferSideLength;

        // Set the scene rectangle size so the scroll area knows how large the scene is

        setSceneRect(0.0f, 0.0f, viewportSize, viewportSize);

        size_t workGroupsPerSide = bufferSideLength / workGroupSideLength;

        crowdRenderer = new CrowdRenderer();
        crowdRenderer->initializeRenderers(viewportSize,
                                           valueRendererLegend,
                                           map,
                                           crowdCalculator->getCosts(),
                                           crowdCalculator->getSpeeds(),
                                           crowdCalculator->getDensitiesDiscomfortsVelocities(),
                                           crowdCalculator->getAverageVelocities(),
                                           crowdCalculator->getPotentials(),
                                           crowdCalculator->getGradients01(),
                                           crowdCalculator->getGradients23(),
                                           crowdCalculator->getSplatAreas(),
                                           crowdCalculator->getWorkGroups(),
                                           crowdCalculator->getWorkItems(),
                                           crowdCalculator->getGroupStates(0),
                                           crowdCalculator->getGroupStates(1),
                                           workGroupsPerSide,
                                           settings);

        isInitialized = true;

        startTimer(0);
    }
    catch (Exception& e)
    {
        // Catching here just to indicate that exceptions must be caught somewhere
        throw;
    }
}


void CrowdScene::drawBackground(QPainter* painter, const QRectF& canvasArea)
{
    if (isInitialized)
    {
        glWidget->makeCurrent();

        if ((painter->paintEngine()->type() != QPaintEngine::OpenGL) &&
            (painter->paintEngine()->type() != QPaintEngine::OpenGL2)   )
        {
            logger->logError("CrowdScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");

            Application::exit(1);
        }
        else
        {
            painter->beginNativePainting();
            {
                glPushClientAttrib( GL_CLIENT_ALL_ATTRIB_BITS );
                glPushAttrib(GL_ALL_ATTRIB_BITS);
                {
                    if (isPrintingProfilerInfo)
                    {
                        clientProfile->stop( &clientProfile->overheadTime );
                    }

                    computeAndRender(canvasArea);

                    //
                    // Evaluate profiling data
                    //

                    if (clientProfile->step())
                    {
                        if (isPrintingProfilerInfo)
                        {
                            QString profilingMessage       = "Client-side execution times:\n\n";
                            QString kernelProfilingMessage = "Single kernel execution times:\n\n";

                            if (isProfilingQueue)
                            {
                                if (isProfilingDetails)
                                {
                                    kernelProfilingMessage += profiler->computeElementsString(NULL, NULL) + "\n\n";
                                }
                            }

                            profilingMessage += clientProfile->getResults(isProfilingDetails);


                            emit profilingInfoChanged(profilingMessage);
                            emit kernelProfilingInfoChanged(kernelProfilingMessage);
                        }

                        clientProfile->clear();
                        profiler->resetElements();
                    }

                    if (isPrintingProfilerInfo)
                    {
                        clientProfile->start( &clientProfile->overheadTime );
                    }
                }
                glPopAttrib();
                glPopClientAttrib();
            }
            painter->endNativePainting();
        }
    }
}


QRectF CrowdScene::itemsBoundingRect() const
{
    return sceneRect();
}


void CrowdScene::setMinimumDensity(float density)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setMinimumDensity(density);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting minimum density:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setMaximumDensity(float density)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setMaximumDensity(density);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting maximum density:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setMaximumSpeed(float speed)
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setMaximumSpeed(speed);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting maximum speed:\n  " + e.message);

        Application::exit(1);
    }
}


float CrowdScene::getMinimumDensity()
{
    return crowdCalculator->getMinimumDensity();
}


float CrowdScene::getMaximumDensity()
{
    return crowdCalculator->getMaximumDensity();
}


void CrowdScene::setInnerLoopCount(uint count)
{
    crowdCalculator->setInnerLoopCount(static_cast<cl_uint> (count));
}


size_t CrowdScene::getViewportSize() const
{
    return viewportSize;
}


void CrowdScene::setDiscomfortBrushRadius(float radius) const
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setDiscomfortBrushRadius(radius);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting discomfort brush radius:\n  " + e.message);

        Application::exit(1);
    }
}


void CrowdScene::setDiscomfortBrushIntensity(float intensity) const
{
    try
    {
        glWidget->makeCurrent();

        crowdCalculator->setDiscomfortBrushIntensity(intensity);
    }
    catch (Exception e)
    {
        logger->logError("An error occurred while setting discomfort brush intensity:\n  " + e.message);

        Application::exit(1);
    }
}


QString CrowdScene::getTotalBufferSizeMessage()
{
    QString message;

    int sum = 0;

    message += "Total VRAM usage. This is the sum of OpenGL texture, OpenGL buffer,\n";
    message += "OpenCL buffer, and OpenCL image memory used by each component in bytes.\n\n";

    message += crowdCalculator->getTotalBufferSizeMessage(&sum);
    message += crowdRenderer->getTotalBufferSizeMessage(&sum);

    message += String::formatMemoryString("Sum ", sum) + " bytes = " + QString::number(sum / 1024 / 1024) + " MB";

    return message;

}
