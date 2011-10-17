#include "MainWindow.h"

#include <QLabel>
#include <QtOpenGL/QGLWidget>

#include "Logger.h"
#include "CrowdScene.h"

#include "Error.h"
#include "graphics/OpenGL.h"
#include "computation/OpenCL.h"
#include "Exception.h"
#include "Application.h"
#include "Number.h"
#include "Settings.h"
#include "SplashScreen.h"


const float MainWindow::WEIGHT_LOWER_BOUND =          0.0f;
const float MainWindow::WEIGHT_UPPER_BOUND = 1000000000.0f;



MainWindow::MainWindow(Logger* logger, QString applicationName, QWidget* parent)
:   QMainWindow(parent),
    positionLabel(NULL),
    zoomLabel(NULL),
    mousePickLabel(NULL),
    agentCountGroup0(NULL),
    agentCountGroup1(NULL),
    agentCountGroup2(NULL),
    agentCountGroup3(NULL),
    agentCountGroup0Parked(NULL),
    agentCountGroup1Parked(NULL),
    agentCountGroup2Parked(NULL),
    agentCountGroup3Parked(NULL),
    agentCountTotal(NULL),
    crowdScene(NULL),
    logger(logger),
    qGLWidget(NULL),
    statusBarSeparator0(NULL),
    statusBarSeparator1(NULL),
    statusBarSeparator2(NULL),
    statusBarSeparator3(NULL),
    statusBarSeparator4(NULL),
    weightsValidator(NULL),
    minimumDensityValidator(NULL),
    maximumDensityValidator(NULL),
    minimumColorScaleValueValidator(NULL),
    maximumColorScaleValueValidator(NULL),
    speedValidator(NULL),
    innerLoopCountValidator(NULL),
    discomfortBrushRadiusValidator(NULL),
    discomfortBrushIntensityValidator(NULL),
    applicationName(applicationName),
    valueRendererLegend(NULL),
    map(NULL),
    innerLoopCount(0),
    outerLoopCount(0)
{
	ui.setupUi(this);

	ui.logWindow->setReadOnly(true);
    ui.logWindow->setFontFamily("Dejavu Sans Mono");
    ui.logWindow->setFontPointSize(10.0f);
    ui.logWindow->document()->setMaximumBlockCount(5000);

    ui.profilingWindow->setFontFamily("Dejavu Sans Mono");
    ui.profilingWindow->setFontPointSize(10.0f);

    ui.kernelProfilingWindow->setFontFamily("Dejavu Sans Mono");
    ui.kernelProfilingWindow->setFontPointSize(10.0f);

    ui.memoryWindow->setFontFamily("Dejavu Sans Mono");
    ui.memoryWindow->setFontPointSize(10.0f);

    ui.dockWidget->setTitleBarWidget(new QWidget());

    setWindowTitle(applicationName);
}


MainWindow::~MainWindow()
{
    delete statusBarSeparator0;
    delete statusBarSeparator1;
    delete statusBarSeparator2;
    delete statusBarSeparator3;
    delete statusBarSeparator4;
    delete crowdScene;
    delete positionLabel;
    delete zoomLabel;
    delete mousePickLabel;
    delete agentCountGroup0;
    delete agentCountGroup1;
    delete agentCountGroup2;
    delete agentCountGroup3;
    delete agentCountGroup0Parked;
    delete agentCountGroup1Parked;
    delete agentCountGroup2Parked;
    delete agentCountGroup3Parked;
    delete agentCountTotal;
    delete qGLWidget;
    delete weightsValidator;
    delete minimumDensityValidator;
    delete maximumDensityValidator;
    delete minimumColorScaleValueValidator;
    delete maximumColorScaleValueValidator;
    delete speedValidator;
    delete innerLoopCountValidator;
    delete discomfortBrushRadiusValidator;
    delete discomfortBrushIntensityValidator;
    delete valueRendererLegend;
    delete map;
}


QTextEdit* MainWindow::getLogWindow()
{
    return ui.logWindow;
}


int MainWindow::sliderValueToOuterLoopCount(int i)
{
    return i;
}


float MainWindow::sliderValueToMapAlpha(int i)
{
    return static_cast<float>(i) / 100.0f;
}


float MainWindow::sliderValueToWorkGroupsAlpha(int i)
{
    return static_cast<float>(i) / 100.0f;
}


float MainWindow::sliderValueToWorkItemsAlpha(int i)
{
    return static_cast<float>(i) / 100.0f;
}


float MainWindow::sliderValueToGroupStatesAlpha(int i)
{
    return static_cast<float>(i) / 100.0f;
}


float MainWindow::sliderValueToGradientArrowsAlpha(int i)
{
    return static_cast<float>(i) / 100.0f;
}


void MainWindow::setMapAlpha(int i)
{
    float alpha = sliderValueToMapAlpha(i);

    emit mapAlphaChanged(alpha);
    emit mapAlphaChanged2(alpha);
}


void MainWindow::setWorkGroupsAlpha(int i)
{
    float alpha = sliderValueToWorkGroupsAlpha(i);

    emit workGroupsAlphaChanged(alpha);
    emit workGroupsAlphaChanged2(alpha);
}


void MainWindow::setWorkItemsAlpha(int i)
{
    float alpha = sliderValueToWorkItemsAlpha(i);

    emit workItemsAlphaChanged(alpha);
    emit workItemsAlphaChanged2(alpha);
}


void MainWindow::setGroupStatesAlpha(int i)
{
    float alpha = sliderValueToGroupStatesAlpha(i);

    emit groupStatesAlphaChanged(alpha);
    emit groupStatesAlphaChanged2(alpha);
}


void MainWindow::setGradientArrowsAlpha(int i)
{
    float alpha = sliderValueToGradientArrowsAlpha(i);

    emit gradientArrowsAlphaChanged(alpha);
    emit gradientArrowsAlphaChanged2(alpha);
}


void MainWindow::setOuterLoopCount(int i)
{
    int count = sliderValueToOuterLoopCount(i);

    outerLoopCount = count;
    updateWorkItemIterations();

    emit outerLoopCountChanged(count);
}


void MainWindow::setGUIElements(bool isValueView, bool isGroupDependent, bool isDirectionDependent) const
{
    ui.frameLegendValue->setVisible(isValueView);
    ui.frameLegendVector->setVisible(!isValueView);

    ui.frameGroups->setVisible(isGroupDependent);
    ui.frameDirections->setVisible(isDirectionDependent);
}


void MainWindow::setFieldRenderState(bool isChecked)
{
    if (isChecked)
    {
        setGradientControlsEnabled(ui.radioButtonShowGradient->isChecked());

        if (ui.radioButtonShowDiscomfort->isChecked())
        {
            emit fieldRenderStateChanged(FieldRenderState::DISCOMFORT);

            setGUIElements(true, false, false);
        }
        else if (ui.radioButtonShowDensity->isChecked())
        {
            emit fieldRenderStateChanged(FieldRenderState::DENSITY);

            setGUIElements(true, false, false);
        }
        else if (ui.radioButtonShowAverageVelocity->isChecked())
        {
            emit fieldRenderStateChanged(FieldRenderState::AVERAGE_VELOCITY);

            setGUIElements(false, false, false);
        }
        else if (ui.radioButtonShowSpeed->isChecked())
        {
            emit fieldRenderStateChanged(FieldRenderState::SPEED);

            setGUIElements(true, false, true);
        }
        else if (ui.radioButtonShowCost->isChecked())
        {
            emit fieldRenderStateChanged(FieldRenderState::COST);

            setGUIElements(true, false, true);
        }
        else if (ui.radioButtonShowPotential->isChecked())
        {
            emit fieldRenderStateChanged(FieldRenderState::POTENTIAL);

            setGUIElements(true, true, false);
        }
        else if (ui.radioButtonShowGradient->isChecked())
        {
            emit fieldRenderStateChanged(FieldRenderState::GRADIENT);

            setGUIElements(false, true, false);
        }
    }
}


void MainWindow::setGradientControlsEnabled(bool isEnabled)
{
    ui.gradientArrowsAlphaLabelName->setEnabled(isEnabled);
    ui.gradientArrowsAlphaSlider->setEnabled(isEnabled);
    ui.gradientArrowsAlphaLabelValue->setEnabled(isEnabled);

    ui.gradientInterpolateLabelName->setEnabled(isEnabled);
    ui.gradientInterpolateYes->setEnabled(isEnabled);
    ui.gradientInterpolateNo->setEnabled(isEnabled);
}


void MainWindow::setAgentGroupRenderState(bool isChecked)
{
    if (isChecked)
    {
        if (ui.radioButtonAgentGroup0->isChecked())
        {
            emit agentGroupRenderStateChanged(AgentGroupRenderState::GROUP0);
        }
        else if (ui.radioButtonAgentGroup1->isChecked())
        {
            emit agentGroupRenderStateChanged(AgentGroupRenderState::GROUP1);

        }
        else if (ui.radioButtonAgentGroup2->isChecked())
        {
            emit agentGroupRenderStateChanged(AgentGroupRenderState::GROUP2);
        }
        else
        {
            emit agentGroupRenderStateChanged(AgentGroupRenderState::GROUP3);
        }
    }
}


void MainWindow::setDirectionRenderState(bool isChecked)
{
    if (isChecked)
    {
        if (ui.radioButtonDirectionNorth->isChecked())
        {
            emit directionRenderStateChanged(DirectionRenderState::NORTH);
        }
        else if (ui.radioButtonDirectionEast->isChecked())
        {
            emit directionRenderStateChanged(DirectionRenderState::EAST);
        }
        else if (ui.radioButtonDirectionSouth->isChecked())
        {
            emit directionRenderStateChanged(DirectionRenderState::SOUTH);
        }
        else
        {
            emit directionRenderStateChanged(DirectionRenderState::WEST);
        }
    }
}


void MainWindow::setGradientFilterState(bool isChecked)
{
    if (isChecked)
    {
        if (ui.gradientInterpolateYes->isChecked())
        {
            emit gradientFilterStateChanged(true);
        }
        else if (ui.gradientInterpolateNo->isChecked())
        {
            emit gradientFilterStateChanged(false);
        }
    }
}


void MainWindow::setUpdateState(bool isChecked)
{
    if (isChecked)
    {
        if (ui.isUpdatingAll->isChecked())
        {
            wasInGroupStateAll = true;

            setGroupStatesAlphaControlsEnabled(false);

            emit updateStateChanged(UpdateState::ALL);
        }
        else if (ui.isUpdatingSelectively->isChecked())
        {
            if (wasInGroupStateAll)
            {
                wasInGroupStateAll = false;
            }

            setGroupStatesAlphaControlsEnabled(true);

            emit updateStateChanged(UpdateState::SELECTIVELY);
        }
    }
}


void MainWindow::setExitMode(bool isChecked)
{
    if (isChecked)
    {
        if (ui.exitPark->isChecked())
        {
            emit exitModeChanged(AgentMover::EXIT_MODE_PARK);
        }
        else if (ui.exitChangeGroup->isChecked())
        {
            emit exitModeChanged(AgentMover::EXIT_MODE_CHANGE_GROUP);
        }
        else if (ui.exitRespawn->isChecked())
        {
            emit exitModeChanged(AgentMover::EXIT_MODE_RESPAWN);
        }
    }
}


void MainWindow::setColorScaleMinSlider(int i)
{
    emit colorScaleMinSliderValueChanged(i);
}


void MainWindow::setColorScaleMaxSlider(int i)
{
    emit colorScaleMaxSliderValueChanged(i);
}


void MainWindow::setIsDrawingSprites(int i)
{
    if (i == Qt::Unchecked)
    {
        emit isDrawingSpritesChanged(false);
    }
    else if (i == Qt::Checked)
    {
        emit isDrawingSpritesChanged(true);
    }
}


void MainWindow::setIsDrawingSplatAreas(int i)
{
    if (i == Qt::Unchecked)
    {
        emit isDrawingSplatAreasChanged(false);
    }
    else if (i == Qt::Checked)
    {
        emit isDrawingSplatAreasChanged(true);
    }
}


void MainWindow::setGroupStatesAlphaControlsEnabled(bool isEnabled)
{
    ui.labelSelectiveUpdateState->setEnabled(isEnabled);
    ui.groupStatesAlphaLabelName->setEnabled(isEnabled);
    ui.groupStatesAlphaSlider->setEnabled(isEnabled);
    ui.groupStatesAlphaLabelValue->setEnabled(isEnabled);
}


void MainWindow::setIsPrintingProfilingInfo(int i)
{
    if (i == Qt::Unchecked)
    {
    	ui.checkBoxProfileDetails->setEnabled(false);
        emit isPrintingProfilingInfoChanged(false);
    }
    else if (i == Qt::Checked)
    {
    	ui.checkBoxProfileDetails->setEnabled(true);
        emit isPrintingProfilingInfoChanged(true);
    }
}


void MainWindow::setIsProfilingDetails(int i)
{
    if (i == Qt::Unchecked)
    {
        emit isProfilingDetailsChanged(false);
    }
    else if (i == Qt::Checked)
    {
        emit isProfilingDetailsChanged(true);
    }
}


void MainWindow::setIsPlaying(bool isChecked)
{
    emit isPlayingChanged(isChecked);
}


void MainWindow::setIsResolvingCollisions(int i)
{
    if (i == Qt::Unchecked)
    {
        emit isResolvingCollisionsChanged(false);
    }
    else if (i == Qt::Checked)
    {
        emit isResolvingCollisionsChanged(true);
    }
}


void MainWindow::showAbout()
{
    QMessageBox about;

    about.setWindowTitle("About " + applicationName);
    about.setText(QString("A crowd simulation using OpenCL") + QString::fromUtf8("™") +
                  " and based on the continuum approach.\n\n" +
                  "Available at https://github.com/hduregger/crowd\n\n" +
                  "Helmut Duregger, 2011.");

    about.exec();
}


void MainWindow::performStep()
{
    ui.actionPlay->setChecked(false);

    emit performStepInvoked();
}


void MainWindow::setMousePick(QPointF position)
{
//    logger->logInfo("Picked " + QString::number( static_cast<int> (position.x()) ) + ":"
//                              + QString::number( static_cast<int> (position.y()) )       );

    emit performMousePick(position);
}


void MainWindow::setMousePickMinimum(QPointF position)
{
//    logger->logInfo("Picked " + QString::number( static_cast<int> (position.x()) ) + ":"
//                              + QString::number( static_cast<int> (position.y()) )       );

    emit performMousePickMinimum(position);
}


void MainWindow::setMousePickMaximum(QPointF position)
{
//    logger->logInfo("Picked " + QString::number( static_cast<int> (position.x()) ) + ":"
//                              + QString::number( static_cast<int> (position.y()) )       );

    emit performMousePickMaximum(position);
}


void MainWindow::setMousePickValue(QString value)
{
    emit mousePickChanged(value);
}


void MainWindow::setMousePickMinimumValue(float value)
{
    emit colorScaleMinChanged(value);
    emit colorScaleMinChangedText(QString::number(value, 'g', 4));
}


void MainWindow::setMousePickMaximumValue(float value)
{
    emit colorScaleMaxChanged(value);
    emit colorScaleMaxChangedText(QString::number(value, 'g', 4));
}


void MainWindow::setProfilingInfo(QString s)
{
    int position = ui.profilingWindow->verticalScrollBar()->value();

    ui.profilingWindow->setText(s);

    ui.profilingWindow->verticalScrollBar()->setValue(position);
}


void MainWindow::setKernelProfilingInfo(QString s)
{
    int position = ui.kernelProfilingWindow->verticalScrollBar()->value();

    ui.kernelProfilingWindow->setText(s);

    ui.kernelProfilingWindow->verticalScrollBar()->setValue(position);
}


void MainWindow::setAgentCounts(std::vector<cl_uint> agentCounts)
{
    agentCountGroup0->setText(QString::number(agentCounts[0]));
    agentCountGroup1->setText(QString::number(agentCounts[1]));
    agentCountGroup2->setText(QString::number(agentCounts[2]));
    agentCountGroup3->setText(QString::number(agentCounts[3]));

    agentCountGroup0Parked->setText(QString::number(agentCounts[4]));
    agentCountGroup1Parked->setText(QString::number(agentCounts[5]));
    agentCountGroup2Parked->setText(QString::number(agentCounts[6]));
    agentCountGroup3Parked->setText(QString::number(agentCounts[7]));


    cl_uint sum = 0;

    for (std::vector<cl_uint>::const_iterator iterator = agentCounts.begin(); iterator != agentCounts.end(); ++iterator)
    {
        sum += (*iterator);
    }

    agentCountTotal->setText(QString::number(sum));
}



void MainWindow::setIsBreakingAfterSolverStep(int i)
{
    if (i == Qt::Unchecked)
    {
        emit isBreakingAfterSolverStepChanged(false);
    }
    else if (i == Qt::Checked)
    {
        emit isBreakingAfterSolverStepChanged(true);
    }
}


void MainWindow::setMousePosition(QPointF position)
{
    int x = static_cast<int> ( position.x() );
    int y = static_cast<int> ( position.y() );

    int max = static_cast<int> ( crowdScene->getViewportSize() ) - 1;

    // Flipp y coordinate

    y = crowdScene->getViewportSize() - y - 1;


    if ( (x >= 0) && (x <= max) && (y >= 0) && (y <= max) )
    {
        QString text = QString("%1 : %2").arg(x, 3, 10, QChar(' ')).arg(y, 3, 10, QChar(' '));

        emit mousePositionChanged(text);
    }
}


void MainWindow::setMousePainted(QPointF position)
{
    int x = static_cast<int> ( position.x() );
    int y = static_cast<int> ( position.y() );

    int max = static_cast<int> ( crowdScene->getViewportSize() ) - 1;

    if ( (x >= 0) && (x <= max) && (y >= 0) && (y <= max) )
    {
        emit mousePaintPositionChanged(position);
    }
}


void MainWindow::costWeightPathLengthEditingFinished()
{
    QString text = ui.lengthLineEdit->text();

    int dummy;

    if (weightsValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousCostWeightPathLengthString = text;

        float f = text.toFloat(NULL);

        emit costWeightPathLengthChanged(f);
    }
    else
    {
        ui.lengthLineEdit->setText(previousCostWeightPathLengthString);
    }
}


void MainWindow::costWeightTimeEditingFinished()
{
    QString text = ui.timeLineEdit->text();

    int dummy;

    if (weightsValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousCostWeightTimeString = text;

        float f = text.toFloat(NULL);

        emit costWeightTimeChanged(f);
    }
    else
    {
        ui.timeLineEdit->setText(previousCostWeightTimeString);
    }
}


void MainWindow::costWeightDiscomfortEditingFinished()
{
    QString text = ui.discomfortLineEdit->text();

    int dummy;

    if (weightsValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousCostWeightDiscomfortString = text;

        float f = text.toFloat(NULL);

        emit costWeightDiscomfortChanged(f);
    }
    else
    {
        ui.discomfortLineEdit->setText(previousCostWeightDiscomfortString);
    }
}


void MainWindow::maximumDensityEditingFinished()
{
    QString text = ui.maximumDensityLineEdit->text();

    int dummy;

    if (maximumDensityValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousMaximumDensityString = text;

        float f = text.toFloat(NULL);

        float minimum = crowdScene->getMinimumDensity();

        if (f <= minimum)
        {
            f = minimum + 0.1f;

            previousMaximumDensityString = QString::number(f);

            ui.maximumDensityLineEdit->setText(previousMaximumDensityString);
        }

        emit maximumDensityChanged(f);
    }
    else
    {
        ui.maximumDensityLineEdit->setText(previousMaximumDensityString);
    }
}


void MainWindow::minimumDensityEditingFinished()
{
    QString text = ui.minimumDensityLineEdit->text();

    int dummy;

    if (minimumDensityValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousMinimumDensityString = text;

        float f = text.toFloat(NULL);

        float maximum = crowdScene->getMaximumDensity();

        if (f >= maximum)
        {
            f = maximum - 0.1f;

            if (f < CrowdCalculator::DENSITY_THRESHOLD)
            {
                f = CrowdCalculator::DENSITY_THRESHOLD;
            }

            previousMinimumDensityString = QString::number(f);

            ui.minimumDensityLineEdit->setText(previousMinimumDensityString);
        }

        emit minimumDensityChanged(f);
    }
    else
    {
        ui.minimumDensityLineEdit->setText(previousMinimumDensityString);
    }
}


void MainWindow::minimumColorScaleValueEditingFinished()
{
    QString text = ui.colorScaleMinLineEdit->text();

    int dummy;

    if (minimumColorScaleValueValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousMinimumColorScaleValueString = text;

        float f = text.toFloat(NULL);

        float maximum = previousMaximumColorScaleValueString.toFloat(NULL);

        if (f >= maximum)
        {
            f = maximum - 0.1f;

            previousMinimumColorScaleValueString = QString::number(f);

            ui.colorScaleMinLineEdit->setText(previousMinimumColorScaleValueString);
        }

        emit colorScaleMinChanged(f);
    }
    else
    {
        ui.colorScaleMinLineEdit->setText(previousMinimumColorScaleValueString);
    }
}


void MainWindow::maximumColorScaleValueEditingFinished()
{
    QString text = ui.colorScaleMaxLineEdit->text();

    int dummy;

    if (maximumColorScaleValueValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousMaximumColorScaleValueString = text;

        float f = text.toFloat(NULL);

        float minimum = previousMinimumColorScaleValueString.toFloat(NULL);

        if (f <= minimum)
        {
            f = minimum + 0.1f;

            previousMaximumColorScaleValueString = QString::number(f);

            ui.colorScaleMaxLineEdit->setText(previousMaximumColorScaleValueString);
        }

        emit colorScaleMaxChanged(f);
    }
    else
    {
        ui.colorScaleMaxLineEdit->setText(previousMaximumColorScaleValueString);
    }
}


void MainWindow::maximumSpeedEditingFinished()
{
    QString text = ui.maximumSpeedLineEdit->text();

    int dummy;

    if (speedValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousMaximumSpeedString = text;

        float f = text.toFloat(NULL);

        emit maximumSpeedChanged(f);
    }
    else
    {
        ui.maximumSpeedLineEdit->setText(previousMaximumSpeedString);
    }
}


void MainWindow::discomfortBrushRadiusEditingFinished()
{
    QString text = ui.discomfortBrushRadiusLineEdit->text();

    int dummy;

    if (discomfortBrushRadiusValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousDiscomfortBrushRadiusString = text;

        float f = text.toFloat(NULL);

        emit discomfortBrushRadiusChanged(f);
    }
    else
    {
        ui.discomfortBrushRadiusLineEdit->setText(previousDiscomfortBrushRadiusString);
    }
}


void MainWindow::discomfortBrushIntensityEditingFinished()
{
    QString text = ui.discomfortBrushIntensityLineEdit->text();

    int dummy;

    if (discomfortBrushIntensityValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousDiscomfortBrushIntensityString = text;

        float f = text.toFloat(NULL);

        emit discomfortBrushIntensityChanged(f);
    }
    else
    {
        ui.discomfortBrushIntensityLineEdit->setText(previousDiscomfortBrushIntensityString);
    }
}


void MainWindow::innerLoopCountEditingFinished()
{
    QString text = ui.innerLoopCountLineEdit->text();

    int dummy;

    if (innerLoopCountValidator->validate(text, dummy) == QValidator::Acceptable)
    {
        previousInnerLoopCountString = text;

        uint i = text.toUInt(NULL);

        innerLoopCount = static_cast<int> (i);
        updateWorkItemIterations();

        emit innerLoopCountChanged(i);
    }
    else
    {
        ui.innerLoopCountLineEdit->setText(previousInnerLoopCountString);
    }
}


void MainWindow::initializeDockWidgetAreas()
{
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
//    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
//    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

}


void MainWindow::initializeMousePositionLabel()
{
    positionLabel = new QLabel();

    positionLabel->setText("0 : 0");
    positionLabel->setToolTip("Item under mouse pointer");

    statusBar()->addPermanentWidget(positionLabel);
}


void MainWindow::initializeZoomIndicatorLabel()
{
    zoomLabel = new QLabel();

    zoomLabel->setText(ui.graphicsView->getZoomFactorString());
    zoomLabel->setToolTip("Current zoom factor\nUse mouse wheel to zoom");

    statusBar()->addPermanentWidget(zoomLabel);
}


void MainWindow::initializeAgentCountLabels()
{
    agentCountGroup0 = new QLabel();
    agentCountGroup1 = new QLabel();
    agentCountGroup2 = new QLabel();
    agentCountGroup3 = new QLabel();

    agentCountGroup0Parked = new QLabel();
    agentCountGroup1Parked = new QLabel();
    agentCountGroup2Parked = new QLabel();
    agentCountGroup3Parked = new QLabel();

    agentCountTotal = new QLabel();

    agentCountGroup0->setText("n/a");
    agentCountGroup0->setToolTip("Active agents in group 0");
    agentCountGroup1->setText("n/a");
    agentCountGroup1->setToolTip("Active agents in group 1");
    agentCountGroup2->setText("n/a");
    agentCountGroup2->setToolTip("Active agents in group 2");
    agentCountGroup3->setText("n/a");
    agentCountGroup3->setToolTip("Active agents in group 3");

    agentCountGroup0Parked->setText("n/a");
    agentCountGroup0Parked->setToolTip("Parked agents in group 0");
    agentCountGroup1Parked->setText("n/a");
    agentCountGroup1Parked->setToolTip("Parked agents in group 1");
    agentCountGroup2Parked->setText("n/a");
    agentCountGroup2Parked->setToolTip("Parked agents in group 2");
    agentCountGroup3Parked->setText("n/a");
    agentCountGroup3Parked->setToolTip("Parked agents in group 3");

    agentCountTotal->setText("n/a");
    agentCountTotal->setToolTip("Total agent count");

    statusBar()->addPermanentWidget(agentCountGroup0);
    statusBar()->addPermanentWidget(agentCountGroup1);
    statusBar()->addPermanentWidget(agentCountGroup2);
    statusBar()->addPermanentWidget(agentCountGroup3);

    statusBar()->addPermanentWidget(statusBarSeparator3);

    statusBar()->addPermanentWidget(agentCountGroup0Parked);
    statusBar()->addPermanentWidget(agentCountGroup1Parked);
    statusBar()->addPermanentWidget(agentCountGroup2Parked);
    statusBar()->addPermanentWidget(agentCountGroup3Parked);

    statusBar()->addPermanentWidget(statusBarSeparator4);

    statusBar()->addPermanentWidget(agentCountTotal);
}


void MainWindow::initializeMousePickIndicatorLabel()
{
    mousePickLabel = new QLabel();

    mousePickLabel->setText("n/a");
    mousePickLabel->setToolTip("Mouse pick value\n[Left Mouse Button]");

    statusBar()->addPermanentWidget(mousePickLabel);
}


void MainWindow::initializeStatusBar()
{
    statusBarSeparator0 = new QFrame();
    statusBarSeparator1 = new QFrame();
    statusBarSeparator2 = new QFrame();
    statusBarSeparator3 = new QFrame();
    statusBarSeparator4 = new QFrame();

    statusBarSeparator0->setFrameShape(QFrame::VLine);
    statusBarSeparator1->setFrameShape(QFrame::VLine);
    statusBarSeparator2->setFrameShape(QFrame::VLine);
    statusBarSeparator3->setFrameShape(QFrame::VLine);
    statusBarSeparator4->setFrameShape(QFrame::VLine);

    initializeAgentCountLabels();

    statusBar()->addPermanentWidget(statusBarSeparator0);
    initializeMousePickIndicatorLabel();

    statusBar()->addPermanentWidget(statusBarSeparator1);
    initializeMousePositionLabel();

    statusBar()->addPermanentWidget(statusBarSeparator2);
    initializeZoomIndicatorLabel();
}


void MainWindow::initializeDirectionLegend()
{
    QPixmap pixmap;
    QString directionLegend = "textures/directionLegend2.png";
    pixmap.load(directionLegend);

    if (pixmap.isNull())
    {
        throw Exception("Could not load direction legend image \"" + directionLegend + "\"");
    }

    pixmap = pixmap.scaled(ui.gradientLegendLabel->width(), ui.gradientLegendLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui.gradientLegendLabel->setPixmap(pixmap);
}


void MainWindow::initializeLineEditValidators()
{
    weightsValidator = new QDoubleValidator(WEIGHT_LOWER_BOUND, WEIGHT_UPPER_BOUND, 2, NULL);

    minimumDensityValidator = new QDoubleValidator(0.5, 1000000000.0, 3, NULL);
    maximumDensityValidator = new QDoubleValidator(0.5, 1000000000.0, 3, NULL);

    speedValidator = new QDoubleValidator(0.1, 100.0, 3, NULL);

    innerLoopCountValidator = new QIntValidator(1, 1000, NULL);

    minimumColorScaleValueValidator = new QDoubleValidator(0.0, 1000000000.0, 3, NULL);
    maximumColorScaleValueValidator = new QDoubleValidator(0.0, 1000000000.0, 3, NULL);

    discomfortBrushRadiusValidator    = new QDoubleValidator(0.5, 1000000000.0, 3, NULL);
    discomfortBrushIntensityValidator = new QDoubleValidator(0.0, 1000000000.0, 3, NULL);
}


void MainWindow::initializeValueLegend()
{
    try
    {
        QImage image = Texture::loadTexture("textures/valueLegend.png", false, false);


        QPixmap pixmap = QPixmap::fromImage(image);

        pixmap = pixmap.scaled(ui.valueLegendLabel->width(),
                               ui.valueLegendLabel->height(),
                               Qt::IgnoreAspectRatio,
                               Qt::SmoothTransformation);

        ui.valueLegendLabel->setPixmap(pixmap);


        image = image.mirrored(false, true);

        size_t pixelCount = image.width() * image.height();

        std::vector<float> data(pixelCount * 4);

        Texture::convertToFloats(image, data, pixelCount);

        valueRendererLegend = new Texture2D(  image.width(),
                                              image.height(),
                                              GL_CLAMP_TO_EDGE,
                                              GL_LINEAR,
                                              GL_LINEAR,
                                              GL_RGBA,
                                              GL_RGBA,
                                              GL_FLOAT,
                                              &data[0]);
    }
    catch (Exception& e)
    {
        throw Exception("Could not load value legend texture: " + e.message);
    }
}


void MainWindow::initializeMap(const QString filename)
{
    try
    {
        QImage image = Texture::loadTexture(filename, false, false);

        if (image.width() != image.height())
        {
            throw Exception("Map texture is not square!");
        }

        image = image.mirrored(false, true);

        size_t pixelCount = image.width() * image.height();

        std::vector<float> data(pixelCount * 4);

        Texture::convertToFloats(image, data, pixelCount);

        map = new Texture2D(  image.width(),
                              image.height(),
                              GL_CLAMP_TO_EDGE,
                              GL_LINEAR,
                              GL_LINEAR,
                              GL_RGBA,
                              GL_RGBA,
                              GL_FLOAT,
                              &data[0]);
    }
    catch (Exception& e)
    {
        throw Exception("Could not load map texture: " + e.message);
    }
}


void MainWindow::initializeActions()
{
    ui.actionPlay->setIcon(QIcon::fromTheme("media-playback-start"));
    ui.actionStep->setIcon(QIcon::fromTheme("media-skip-forward"));
    ui.actionRewind->setIcon(QIcon::fromTheme("media-seek-backward"));

    ui.actionZoom_in->setIcon(QIcon::fromTheme("zoom-in"));
    ui.actionZoom_out->setIcon(QIcon::fromTheme("zoom-out"));
    ui.actionZoom_1_1->setIcon(QIcon::fromTheme("zoom-original"));

    ui.actionExit->setIcon(QIcon::fromTheme("application-exit"));

    ui.actionZoom_in->setIconVisibleInMenu(true);
    ui.actionZoom_out->setIconVisibleInMenu(true);
    ui.actionZoom_1_1->setIconVisibleInMenu(true);
    ui.actionExit->setIconVisibleInMenu(true);
}


void MainWindow::initialize(const Settings*     settings,
                                  QApplication* application)
{
    statusBar()->showMessage("Initializing...", 0);

    qGLWidget = createQGLWidget();

    ui.graphicsView->setVisible(false);


    initializeDockWidgetAreas();

    initializeActions();

    initializeStatusBar();

    initializeDirectionLegend();
    initializeValueLegend();

    initializeLineEditValidators();

    initializeMap(settings->mapFile);

    //
    // Create scene
    //


    // Retrieve window background color of theme to clear GL viewport with

    qreal r;
    qreal g;
    qreal b;
    qreal a;

    ui.centralwidget->palette().window().color().getRgbF(&r, &g, &b, &a);

    Vector4 color(static_cast<float> (r), static_cast<float> (g), static_cast<float> (b), 1.0f);

    crowdScene = new CrowdScene(qGLWidget, logger, applicationName, color);

    //
    // Setup view
    //

    ui.graphicsView->setViewport(qGLWidget);
    ui.graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui.graphicsView->setCacheMode(QGraphicsView::CacheNone);
    ui.graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
//    ui.graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    ui.graphicsView->setScene(crowdScene);
    ui.graphicsView->setMouseTracking(true);


    //
    // Connect message system
    //

    connectSignalsAndSlots();

	QPixmap pixmap("textures/splash.png");

	SplashScreen splash(pixmap);
	splash.show();

	logger->setSplash(&splash, application);

	// Handle user clicking away splash

    application->processEvents();

    crowdScene->initialize( settings,
                            valueRendererLegend,
                            map);

    QString totalBufferSizeMessage = crowdScene->getTotalBufferSizeMessage();
    ui.memoryWindow->setText(totalBufferSizeMessage);


    //
    // Propagate startup values
    //

    initializeStartupValues(settings);

    show();

    logger->setSplash(NULL, NULL);

    // Hide splash

    splash.finish(this);

    statusBar()->showMessage("Ready", 0);
}


void MainWindow::initializeStartupValues(const Settings* settings)
{

    // Set setting values

    ui.iterationsSlider->setValue(settings->outerIterations);

    ui.lengthLineEdit->setText(QString::number(settings->costWeightLength));
    ui.timeLineEdit->setText(QString::number(settings->costWeightTime));
    ui.discomfortLineEdit->setText(QString::number(settings->costWeightDiscomfort));

    switch (settings->movementMode)
    {
        case 0:
        {
            ui.exitPark->setChecked(true);
            break;
        }

        case 1:
        {
            ui.exitChangeGroup->setChecked(true);
            break;
        }

        default:
        {
            ui.exitRespawn->setChecked(true);
            break;
        }
    }

    //
    // Propagate initial slider values
    //

    setOuterLoopCount(ui.iterationsSlider->value());
    setMapAlpha(ui.mapAlphaSlider->value());
    setWorkGroupsAlpha(ui.workGroupsAlphaSlider->value());
    setWorkItemsAlpha(ui.workItemsAlphaSlider->value());
    setGroupStatesAlpha(ui.groupStatesAlphaSlider->value());
    setGradientArrowsAlpha(ui.gradientArrowsAlphaSlider->value());

    //
    // Propagate initial checkboxes value
    //

    setIsDrawingSprites(ui.isDrawingSprites->checkState());
    setIsDrawingSplatAreas(ui.checkBoxIsDrawingSplatAreas->checkState());
    setIsResolvingCollisions(ui.resolveCollisionsCheckBox->checkState());
    setIsPrintingProfilingInfo(ui.checkBoxPrintProfiling->checkState());
    setIsProfilingDetails(ui.checkBoxProfileDetails->checkState());
    setIsBreakingAfterSolverStep(ui.isBreakingAfterSolverStep->checkState());

    wasInGroupStateAll = false;

    //
    // Propagate initial radio button value
    //

    setFieldRenderState(true);
    setAgentGroupRenderState(true);
    setDirectionRenderState(true);
    setUpdateState(true);
    setExitMode(true);
    setGradientFilterState(true);

    //
    // Propagate initial play action value
    //

    setIsPlaying(ui.actionPlay->isChecked());

    ui.graphicsView->setVisible(true);

    //
    // Propagate initial cost weights
    //

    previousCostWeightPathLengthString  = ui.lengthLineEdit->text();
    previousCostWeightTimeString        = ui.timeLineEdit->text();
    previousCostWeightDiscomfortString  = ui.discomfortLineEdit->text();

    emit costWeightPathLengthChanged(   previousCostWeightPathLengthString.toFloat(NULL));
    emit costWeightTimeChanged(         previousCostWeightTimeString.toFloat(NULL));
    emit costWeightDiscomfortChanged(   previousCostWeightDiscomfortString.toFloat(NULL));

    //
    // Propagate initial density values
    //

    previousMinimumDensityString = ui.minimumDensityLineEdit->text();
    previousMaximumDensityString = ui.maximumDensityLineEdit->text();

    emit minimumDensityChanged(previousMinimumDensityString.toFloat(NULL));
    emit maximumDensityChanged(previousMaximumDensityString.toFloat(NULL));

    //
    // Propagate initial speed value
    //

    previousMaximumSpeedString = ui.maximumSpeedLineEdit->text();

    emit maximumSpeedChanged(previousMaximumSpeedString.toFloat(NULL));

    //
    // Propagate initial inner loop count
    //

    previousInnerLoopCountString = ui.innerLoopCountLineEdit->text();
    innerLoopCount = previousInnerLoopCountString.toInt(NULL);

    emit innerLoopCountChanged(innerLoopCount);

    //
    // Propagate initial discomfort brush values
    //

    previousDiscomfortBrushRadiusString = ui.discomfortBrushRadiusLineEdit->text();

    emit discomfortBrushRadiusChanged(previousDiscomfortBrushRadiusString.toFloat(NULL));

    previousDiscomfortBrushIntensityString = ui.discomfortBrushIntensityLineEdit->text();

    emit discomfortBrushIntensityChanged(previousDiscomfortBrushIntensityString.toFloat(NULL));

    ui.innerUnrollFactor->setNum(PotentialCalculator::INNER_LOOP_UNROLL_FACTOR);



    updateWorkItemIterations();
}


void MainWindow::connectSignalsAndSlots()
{
    //
    // Connections for pushing GUI controls settings into scene
    //

    QObject::connect(ui.iterationsSlider, SIGNAL(valueChanged(int)), this, SLOT(setOuterLoopCount(int)));
    QObject::connect(this, SIGNAL(outerLoopCountChanged(int)), ui.iterationsLabelValue, SLOT(setNum(int)));
    QObject::connect(this, SIGNAL(outerLoopCountChanged(int)), crowdScene, SLOT(setOuterLoopCount(int)));

    QObject::connect(this, SIGNAL(colorScaleMinChangedText(QString)), ui.colorScaleMinLineEdit, SLOT(setText(QString)));
    QObject::connect(this, SIGNAL(colorScaleMinChanged(float)), crowdScene, SLOT(setColorScaleMin(float)));

    QObject::connect(this, SIGNAL(colorScaleMaxChangedText(QString)), ui.colorScaleMaxLineEdit, SLOT(setText(QString)));
    QObject::connect(this, SIGNAL(colorScaleMaxChanged(float)), crowdScene, SLOT(setColorScaleMax(float)));

    QObject::connect(ui.colorScaleMinLineEdit, SIGNAL(editingFinished()), this, SLOT(minimumColorScaleValueEditingFinished()));
    QObject::connect(ui.colorScaleMaxLineEdit, SIGNAL(editingFinished()), this, SLOT(maximumColorScaleValueEditingFinished()));

    QObject::connect(ui.mapAlphaSlider, SIGNAL(valueChanged(int)), this, SLOT(setMapAlpha(int)));
    QObject::connect(this, SIGNAL(mapAlphaChanged(double)), ui.mapAlphaLabelValue, SLOT(setNum(double)));
    QObject::connect(this, SIGNAL(mapAlphaChanged2(GLfloat)), crowdScene, SLOT(setMapAlpha(GLfloat)));

    QObject::connect(ui.workGroupsAlphaSlider, SIGNAL(valueChanged(int)), this, SLOT(setWorkGroupsAlpha(int)));
    QObject::connect(this, SIGNAL(workGroupsAlphaChanged(double)), ui.workGroupsAlphaLabelValue, SLOT(setNum(double)));
    QObject::connect(this, SIGNAL(workGroupsAlphaChanged2(GLfloat)), crowdScene, SLOT(setWorkGroupsAlpha(GLfloat)));

    QObject::connect(ui.workItemsAlphaSlider, SIGNAL(valueChanged(int)), this, SLOT(setWorkItemsAlpha(int)));
    QObject::connect(this, SIGNAL(workItemsAlphaChanged(double)), ui.workItemsAlphaLabelValue, SLOT(setNum(double)));
    QObject::connect(this, SIGNAL(workItemsAlphaChanged2(GLfloat)), crowdScene, SLOT(setWorkItemsAlpha(GLfloat)));

    QObject::connect(ui.groupStatesAlphaSlider, SIGNAL(valueChanged(int)), this, SLOT(setGroupStatesAlpha(int)));
    QObject::connect(this, SIGNAL(groupStatesAlphaChanged(double)), ui.groupStatesAlphaLabelValue, SLOT(setNum(double)));
    QObject::connect(this, SIGNAL(groupStatesAlphaChanged2(GLfloat)), crowdScene, SLOT(setGroupStatesAlpha(GLfloat)));

    QObject::connect(ui.gradientArrowsAlphaSlider, SIGNAL(valueChanged(int)), this, SLOT(setGradientArrowsAlpha(int)));
    QObject::connect(this, SIGNAL(gradientArrowsAlphaChanged(double)), ui.gradientArrowsAlphaLabelValue, SLOT(setNum(double)));
    QObject::connect(this, SIGNAL(gradientArrowsAlphaChanged2(GLfloat)), crowdScene, SLOT(setGradientArrowsAlpha(GLfloat)));

    QObject::connect(ui.resolveCollisionsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setIsResolvingCollisions(int)));
    QObject::connect(this, SIGNAL(isResolvingCollisionsChanged(bool)), crowdScene, SLOT(setIsResolvingCollisions(bool)));

    // Discomfort brush

    QObject::connect(ui.discomfortBrushRadiusLineEdit,    SIGNAL(editingFinished()), this, SLOT(discomfortBrushRadiusEditingFinished()));
    QObject::connect(ui.discomfortBrushIntensityLineEdit, SIGNAL(editingFinished()), this, SLOT(discomfortBrushIntensityEditingFinished()));

    QObject::connect(this, SIGNAL(discomfortBrushRadiusChanged(float)), crowdScene, SLOT(setDiscomfortBrushRadius(float)));
    QObject::connect(this, SIGNAL(discomfortBrushIntensityChanged(float)), crowdScene, SLOT(setDiscomfortBrushIntensity(float)));

    // Zooming

    QObject::connect(ui.graphicsView, SIGNAL(zoomChanged(float)), crowdScene, SLOT(setScale(float)));
    QObject::connect(ui.graphicsView, SIGNAL(zoomChanged(QString)), zoomLabel, SLOT(setText(QString)));

    // Field render states

    QObject::connect(ui.radioButtonShowDiscomfort, SIGNAL(toggled(bool)), this, SLOT(setFieldRenderState(bool)));
    QObject::connect(ui.radioButtonShowDensity, SIGNAL(toggled(bool)), this, SLOT(setFieldRenderState(bool)));
    QObject::connect(ui.radioButtonShowAverageVelocity, SIGNAL(toggled(bool)), this, SLOT(setFieldRenderState(bool)));
    QObject::connect(ui.radioButtonShowSpeed, SIGNAL(toggled(bool)), this, SLOT(setFieldRenderState(bool)));
    QObject::connect(ui.radioButtonShowCost, SIGNAL(toggled(bool)), this, SLOT(setFieldRenderState(bool)));
    QObject::connect(ui.radioButtonShowPotential, SIGNAL(toggled(bool)), this, SLOT(setFieldRenderState(bool)));
    QObject::connect(ui.radioButtonShowGradient, SIGNAL(toggled(bool)), this, SLOT(setFieldRenderState(bool)));

    QObject::connect(this, SIGNAL(fieldRenderStateChanged(FieldRenderState::State)), crowdScene, SLOT(setFieldRenderState(FieldRenderState::State)));

    // Agent group render states

    QObject::connect(ui.radioButtonAgentGroup0, SIGNAL(toggled(bool)), this, SLOT(setAgentGroupRenderState(bool)));
    QObject::connect(ui.radioButtonAgentGroup1, SIGNAL(toggled(bool)), this, SLOT(setAgentGroupRenderState(bool)));
    QObject::connect(ui.radioButtonAgentGroup2, SIGNAL(toggled(bool)), this, SLOT(setAgentGroupRenderState(bool)));
    QObject::connect(ui.radioButtonAgentGroup3, SIGNAL(toggled(bool)), this, SLOT(setAgentGroupRenderState(bool)));

    QObject::connect(this, SIGNAL(agentGroupRenderStateChanged(AgentGroupRenderState::State)), crowdScene, SLOT(setAgentGroupRenderState(AgentGroupRenderState::State)));

    // Direction render states

    QObject::connect(ui.radioButtonDirectionNorth, SIGNAL(toggled(bool)), this, SLOT(setDirectionRenderState(bool)));
    QObject::connect(ui.radioButtonDirectionEast,  SIGNAL(toggled(bool)), this, SLOT(setDirectionRenderState(bool)));
    QObject::connect(ui.radioButtonDirectionSouth, SIGNAL(toggled(bool)), this, SLOT(setDirectionRenderState(bool)));
    QObject::connect(ui.radioButtonDirectionWest,  SIGNAL(toggled(bool)), this, SLOT(setDirectionRenderState(bool)));

    QObject::connect(this, SIGNAL(directionRenderStateChanged(DirectionRenderState::State)), crowdScene, SLOT(setDirectionRenderState(DirectionRenderState::State)));

    // Gradient direction render state

    QObject::connect(ui.gradientInterpolateYes, SIGNAL(toggled(bool)), this, SLOT(setGradientFilterState(bool)));
    QObject::connect(ui.gradientInterpolateNo,  SIGNAL(toggled(bool)), this, SLOT(setGradientFilterState(bool)));

    QObject::connect(this, SIGNAL(gradientFilterStateChanged(bool)), crowdScene, SLOT(setGradientFilterState(bool)));

    // Update methods

    QObject::connect(ui.isUpdatingAll,         SIGNAL(toggled(bool)), this, SLOT(setUpdateState(bool)));
    QObject::connect(ui.isUpdatingSelectively, SIGNAL(toggled(bool)), this, SLOT(setUpdateState(bool)));

    QObject::connect(this, SIGNAL(updateStateChanged(UpdateState::State)), crowdScene, SLOT(setUpdateState(UpdateState::State)));

    // Exit mode

    QObject::connect(ui.exitPark,         SIGNAL(toggled(bool)), this, SLOT(setExitMode(bool)));
    QObject::connect(ui.exitChangeGroup,  SIGNAL(toggled(bool)), this, SLOT(setExitMode(bool)));
    QObject::connect(ui.exitRespawn,      SIGNAL(toggled(bool)), this, SLOT(setExitMode(bool)));

    QObject::connect(this, SIGNAL(exitModeChanged(cl_int)), crowdScene, SLOT(setExitMode(cl_int)));

    // Optional rendering check boxes

    QObject::connect(ui.isDrawingSprites, SIGNAL(stateChanged(int)), this, SLOT(setIsDrawingSprites(int)));
    QObject::connect(this, SIGNAL(isDrawingSpritesChanged(bool)), crowdScene, SLOT(setIsDrawingSprites(bool)));

    QObject::connect(ui.checkBoxIsDrawingSplatAreas, SIGNAL(stateChanged(int)), this, SLOT(setIsDrawingSplatAreas(int)));
    QObject::connect(this, SIGNAL(isDrawingSplatAreasChanged(bool)), crowdScene, SLOT(setIsDrawingSplatAreas(bool)));

    // Actions

    QObject::connect(ui.actionPlay, SIGNAL(toggled(bool)), this, SLOT(setIsPlaying(bool)));
    QObject::connect(this, SIGNAL(isPlayingChanged(bool)), crowdScene, SLOT(setIsPlaying(bool)));

    QObject::connect(ui.actionStep, SIGNAL(triggered(bool)), this, SLOT(performStep()));
    QObject::connect(this, SIGNAL(performStepInvoked()), crowdScene, SLOT(performStep()));

    QObject::connect(ui.actionRewind, SIGNAL(triggered(bool)), crowdScene, SLOT(performRewind()));

    QObject::connect(ui.actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAbout()));

    // Mouse picking

    QObject::connect(ui.graphicsView, SIGNAL(mousePicked(QPointF)), this, SLOT(setMousePick(QPointF)));
    QObject::connect(this, SIGNAL(performMousePick(QPointF)), crowdScene, SLOT(performMousePick(QPointF)));
    QObject::connect(crowdScene, SIGNAL(mousePickValueChanged(QString)), this, SLOT(setMousePickValue(QString)));
    QObject::connect(this, SIGNAL(mousePickChanged(QString)), mousePickLabel, SLOT(setText(QString)));

    QObject::connect(ui.graphicsView, SIGNAL(mousePickedMinimum(QPointF)), this, SLOT(setMousePickMinimum(QPointF)));
    QObject::connect(this, SIGNAL(performMousePickMinimum(QPointF)), crowdScene, SLOT(performMousePickMinimum(QPointF)));
    QObject::connect(crowdScene, SIGNAL(mousePickMinimumValueChanged(float)), this, SLOT(setMousePickMinimumValue(float)));

    QObject::connect(ui.graphicsView, SIGNAL(mousePickedMaximum(QPointF)), this, SLOT(setMousePickMaximum(QPointF)));
    QObject::connect(this, SIGNAL(performMousePickMaximum(QPointF)), crowdScene, SLOT(performMousePickMaximum(QPointF)));
    QObject::connect(crowdScene, SIGNAL(mousePickMaximumValueChanged(float)), this, SLOT(setMousePickMaximumValue(float)));

    // Mouse painting

    QObject::connect(ui.graphicsView, SIGNAL(mousePainted(QPointF)), this, SLOT(setMousePainted(QPointF)));
    QObject::connect(this, SIGNAL(mousePaintPositionChanged(QPointF)), crowdScene, SLOT(setMousePaintPosition(QPointF)));

    // Mouse movement

    QObject::connect(ui.graphicsView, SIGNAL(mouseMoved(QPointF)), this, SLOT(setMousePosition(QPointF)));
    QObject::connect(this, SIGNAL(mousePositionChanged(QString)), positionLabel, SLOT(setText(QString)));

    // Profiling check box

    QObject::connect(ui.checkBoxPrintProfiling, SIGNAL(stateChanged(int)), this, SLOT(setIsPrintingProfilingInfo(int)));
    QObject::connect(this, SIGNAL(isPrintingProfilingInfoChanged(bool)), crowdScene, SLOT(setIsPrintingProfilingInfo(bool)));

    // Profiling details check box

    QObject::connect(ui.checkBoxProfileDetails, SIGNAL(stateChanged(int)), this, SLOT(setIsProfilingDetails(int)));
    QObject::connect(this, SIGNAL(isProfilingDetailsChanged(bool)), crowdScene, SLOT(setIsProfilingDetails(bool)));

    // Cost weights

    QObject::connect(ui.lengthLineEdit, SIGNAL(editingFinished()), this, SLOT(costWeightPathLengthEditingFinished()));
    QObject::connect(ui.timeLineEdit, SIGNAL(editingFinished()), this, SLOT(costWeightTimeEditingFinished()));
    QObject::connect(ui.discomfortLineEdit, SIGNAL(editingFinished()), this, SLOT(costWeightDiscomfortEditingFinished()));

    QObject::connect(this, SIGNAL(costWeightPathLengthChanged(float)), crowdScene, SLOT(setCostWeightPathLength(float)));
    QObject::connect(this, SIGNAL(costWeightTimeChanged(float)), crowdScene, SLOT(setCostWeightTime(float)));
    QObject::connect(this, SIGNAL(costWeightDiscomfortChanged(float)), crowdScene, SLOT(setCostWeightDiscomfort(float)));

    // Density

    QObject::connect(ui.minimumDensityLineEdit, SIGNAL(editingFinished()), this, SLOT(minimumDensityEditingFinished()));
    QObject::connect(ui.maximumDensityLineEdit, SIGNAL(editingFinished()), this, SLOT(maximumDensityEditingFinished()));

    QObject::connect(this, SIGNAL(minimumDensityChanged(float)), crowdScene, SLOT(setMinimumDensity(float)));
    QObject::connect(this, SIGNAL(maximumDensityChanged(float)), crowdScene, SLOT(setMaximumDensity(float)));

    // Speed

    QObject::connect(ui.maximumSpeedLineEdit, SIGNAL(editingFinished()), this, SLOT(maximumSpeedEditingFinished()));

    QObject::connect(this, SIGNAL(maximumSpeedChanged(float)), crowdScene, SLOT(setMaximumSpeed(float)));

    // Inner loop count

    QObject::connect(ui.innerLoopCountLineEdit, SIGNAL(editingFinished()), this, SLOT(innerLoopCountEditingFinished()));

    QObject::connect(this, SIGNAL(innerLoopCountChanged(uint)), crowdScene, SLOT(setInnerLoopCount(uint)));

    //
    // Connections for getting data out of scene represented in the GUI
    //

    QObject::connect(crowdScene, SIGNAL(colorScaleMinChanged(float)), this, SLOT(setMousePickMinimumValue(float)));
    QObject::connect(crowdScene, SIGNAL(colorScaleMaxChanged(float)), this, SLOT(setMousePickMaximumValue(float)));

    QObject::connect(crowdScene, SIGNAL(profilingInfoChanged(QString)), this, SLOT(setProfilingInfo(QString)));
    QObject::connect(crowdScene, SIGNAL(kernelProfilingInfoChanged(QString)), this, SLOT(setKernelProfilingInfo(QString)));

    QObject::connect(crowdScene, SIGNAL(agentCountsChanged(std::vector<cl_uint>)), this, SLOT(setAgentCounts(std::vector<cl_uint>)));


    // Solver stepping

    QObject::connect(ui.isBreakingAfterSolverStep, SIGNAL(stateChanged(int)), this, SLOT(setIsBreakingAfterSolverStep(int)));
    QObject::connect(this, SIGNAL(isBreakingAfterSolverStepChanged(bool)), crowdScene, SLOT(setIsBreakingAfterSolverStep(bool)));
}



QGLWidget* MainWindow::createQGLWidget()
{
    QGLWidget* qGLWidget;

    QGLFormat format;

    format.setDoubleBuffer(true);
    format.setSampleBuffers(false);
    format.setRgba(true);
    format.setAlpha(true);
    format.setDepth(false);
    format.setOverlay(false); // Enabling the overlay plane will cause QGLWidget to create an additional context in an overlay plane.
    format.setPlane(0); // 0 is the normal plane, 1 is the first overlay plane, -1 is the first underlay plane.
    //   format.setDirectRendering(false);
    format.setVersion(4, 1);
    format.setProfile(QGLFormat::CompatibilityProfile);
//    format.setProfile(QGLFormat::CoreProfile);

    qGLWidget = new QGLWidget(format);

    if (!QGLFormat::hasOpenGL())
    {
        throw Exception("This system has no OpenGL support");
    }

    qGLWidget->makeCurrent();

    logger->logInfo("OpenGL version: " + OpenGL::getVersion() + ".");

    return qGLWidget;
}


void MainWindow::updateWorkItemIterations()
{
    ui.workItemIterations->setNum(outerLoopCount * innerLoopCount * PotentialCalculator::INNER_LOOP_UNROLL_FACTOR);
}
