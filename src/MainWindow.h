#ifndef CROWDQT_H
#define CROWDQT_H

#include <QtGui/QMainWindow>
#include <QApplication>

#include "ui_crowdqt.h"

#include "CrowdScene.h"
#include "graphics/Texture2D.h"
#include "Settings.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

            static const float WEIGHT_LOWER_BOUND;
            static const float WEIGHT_UPPER_BOUND;

            MainWindow(Logger* logger, QString applicationName, QWidget* parent = 0);
            ~MainWindow();

    int     sliderValueToOuterLoopCount(int i);

    float   sliderValueToMapAlpha(int i);
    float   sliderValueToWorkGroupsAlpha(int i);
    float   sliderValueToWorkItemsAlpha(int i);
    float   sliderValueToGroupStatesAlpha(int i);
    float   sliderValueToGradientArrowsAlpha(int i);

    void    connectSignalsAndSlots();

    QTextEdit*  getLogWindow();

    void        initialize(const Settings*     settings,
                                 QApplication* application);

public slots:

    void    setFieldRenderState(bool isChecked);
    void    setAgentGroupRenderState(bool isChecked);
    void    setDirectionRenderState(bool isChecked);
    void    setUpdateState(bool isChecked);
    void    setExitMode(bool isChecked);
    void    setOuterLoopCount(int i);
    void    setMapAlpha(int i);
    void    setWorkGroupsAlpha(int i);
    void    setWorkItemsAlpha(int i);
    void    setGroupStatesAlpha(int i);
    void    setGradientArrowsAlpha(int i);
    void    setGradientFilterState(bool isChecked);

    void    setColorScaleMinSlider(int i);
    void    setColorScaleMaxSlider(int i);

    void    setIsDrawingSprites(int i);
    void    setIsDrawingSplatAreas(int i);

    void    setIsPrintingProfilingInfo(int i);
    void    setIsProfilingDetails(int i);
    void    setIsBreakingAfterSolverStep(int i);

    void    setIsPlaying(bool isChecked);
    void    performStep();

    void    setMousePick(QPointF position);
    void    setMousePickValue(QString value);
    void    setMousePickMinimum(QPointF position);
    void    setMousePickMinimumValue(float value);
    void    setMousePickMaximum(QPointF position);
    void    setMousePickMaximumValue(float value);

    void    setProfilingInfo(QString s);
    void    setKernelProfilingInfo(QString s);

    void    setMousePosition(QPointF position);
    void    setMousePainted(QPointF position);

    void    costWeightPathLengthEditingFinished();
    void    costWeightTimeEditingFinished();
    void    costWeightDiscomfortEditingFinished();

    void    maximumDensityEditingFinished();
    void    minimumDensityEditingFinished();

    void    minimumColorScaleValueEditingFinished();
    void    maximumColorScaleValueEditingFinished();

    void    maximumSpeedEditingFinished();

    void    innerLoopCountEditingFinished();

    void    discomfortBrushRadiusEditingFinished();
    void    discomfortBrushIntensityEditingFinished();

    void    setIsResolvingCollisions(int i);

    void    showAbout();

    void    setAgentCounts(std::vector<cl_uint> agentCounts);

signals:

    void    mapAlphaChanged(double d);
    void    mapAlphaChanged2(GLfloat f);

    void    workGroupsAlphaChanged(double d);
    void    workGroupsAlphaChanged2(GLfloat f);

    void    workItemsAlphaChanged(double d);
    void    workItemsAlphaChanged2(GLfloat f);

    void    groupStatesAlphaChanged(double d);
    void    groupStatesAlphaChanged2(GLfloat f);

    void    gradientArrowsAlphaChanged(double d);
    void    gradientArrowsAlphaChanged2(GLfloat f);

    void    outerLoopCountChanged(int i);

    void    colorScaleMinChanged(float f);
    void    colorScaleMaxChanged(float f);

    void    colorScaleMinChangedText(QString s);
    void    colorScaleMaxChangedText(QString s);

    void    fieldRenderStateChanged(FieldRenderState::State s);
    void    agentGroupRenderStateChanged(AgentGroupRenderState::State s);
    void    directionRenderStateChanged(DirectionRenderState::State s);
    void    updateStateChanged(UpdateState::State s);
    void    exitModeChanged(cl_int exitMode);

    void    gradientFilterStateChanged(bool isInterpolating);

    void    colorScaleMinSliderValueChanged(int i);
    void    colorScaleMaxSliderValueChanged(int i);

    void    isDrawingSpritesChanged(bool);
    void    isDrawingSplatAreasChanged(bool);
    void    isPrintingProfilingInfoChanged(bool);
    void    isProfilingDetailsChanged(bool);

    void    isPlayingChanged(bool);
    void    performStepInvoked();

    void    performMousePick(QPointF position);
    void    performMousePickMinimum(QPointF position);
    void    performMousePickMaximum(QPointF position);

    void    mousePickChanged(QString s);
    void    mousePositionChanged(QString s);

    void    mousePaintPositionChanged(QPointF position);

    void    costWeightPathLengthChanged(float f);
    void    costWeightTimeChanged(float f);
    void    costWeightDiscomfortChanged(float f);

    void    minimumDensityChanged(float f);
    void    maximumDensityChanged(float f);

    void    maximumSpeedChanged(float f);

    void    innerLoopCountChanged(uint i);

    void    isResolvingCollisionsChanged(bool b);

    void    isBreakingAfterSolverStepChanged(bool b);

    void    discomfortBrushRadiusChanged(float f);
    void    discomfortBrushIntensityChanged(float f);

private:

    Ui::CrowdQtClass    ui;

    QLabel*             positionLabel;
    QLabel*             zoomLabel;
    QLabel*             mousePickLabel;

    QLabel*             agentCountGroup0;
    QLabel*             agentCountGroup1;
    QLabel*             agentCountGroup2;
    QLabel*             agentCountGroup3;

    QLabel*             agentCountGroup0Parked;
    QLabel*             agentCountGroup1Parked;
    QLabel*             agentCountGroup2Parked;
    QLabel*             agentCountGroup3Parked;

    QLabel*             agentCountTotal;



    CrowdScene*         crowdScene;
    Logger*             logger;

    QGLWidget*          qGLWidget;

    QFrame*             statusBarSeparator0;
    QFrame*             statusBarSeparator1;
    QFrame*             statusBarSeparator2;
    QFrame*             statusBarSeparator3;
    QFrame*             statusBarSeparator4;

    QDoubleValidator*   weightsValidator;
    QDoubleValidator*   minimumDensityValidator;
    QDoubleValidator*   maximumDensityValidator;
    QDoubleValidator*   minimumColorScaleValueValidator;
    QDoubleValidator*   maximumColorScaleValueValidator;
    QDoubleValidator*   speedValidator;
    QIntValidator*      innerLoopCountValidator;
    QDoubleValidator*   discomfortBrushRadiusValidator;
    QDoubleValidator*   discomfortBrushIntensityValidator;

    QString             previousCostWeightPathLengthString;
    QString             previousCostWeightTimeString;
    QString             previousCostWeightDiscomfortString;

    QString             previousMinimumColorScaleValueString;
    QString             previousMaximumColorScaleValueString;

    QString             previousMinimumDensityString;
    QString             previousMaximumDensityString;

    QString             previousMaximumSpeedString;

    QString             previousInnerLoopCountString;

    QString             previousDiscomfortBrushRadiusString;
    QString             previousDiscomfortBrushIntensityString;

    QString             applicationName;

    bool                wasInGroupStateAll;

    Texture2D*          valueRendererLegend;
    Texture2D*          map;

    int                 innerLoopCount;
    int                 outerLoopCount;

    QGLWidget*          createQGLWidget();


    void                initializeView(QGraphicsView* view);
    void                initializeDockWidgetAreas();
    void                initializeZoomIndicatorLabel();
    void                initializeMousePositionLabel();
    void                initializeAgentCountLabels();
    void                initializeMousePickIndicatorLabel();
    void                initializeStatusBar();
    void                initializeDirectionLegend();
    void                initializeValueLegend();
    void                initializeActions();
    void                initializeLineEditValidators();
    void                initializeMap(const QString filename);

    void                initializeStartupValues(const Settings* settings);

    void                setGUIElements(bool isValueView, bool isGroupDependent, bool isDirectionDependent) const;

    void                setGroupStatesAlphaControlsEnabled(bool isEnabled);
    void                setGradientControlsEnabled(bool isEnabled);

    void                updateWorkItemIterations();
};

#endif // CROWDQT_H
