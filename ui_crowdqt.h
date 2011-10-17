/********************************************************************************
** Form generated from reading UI file 'crowdqt.ui'
**
** Created: Mon Sep 5 14:24:06 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CROWDQT_H
#define UI_CROWDQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <src/GraphicsView.h>

QT_BEGIN_NAMESPACE

class Ui_CrowdQtClass
{
public:
    QAction *actionExit;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionZoom_1_1;
    QAction *actionRewind;
    QAction *actionPlay;
    QAction *actionStep;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    GraphicsView *graphicsView;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_10;
    QFrame *frameLegendVector;
    QLabel *labelSouth;
    QLabel *labelEast;
    QLabel *gradientLegendLabel;
    QLabel *labelNorth;
    QLabel *labelWest;
    QLabel *label_10;
    QFrame *frameLegendValue;
    QLabel *valueLegendLabel;
    QLabel *label_11;
    QLineEdit *colorScaleMaxLineEdit;
    QLineEdit *colorScaleMinLineEdit;
    QLabel *label_9;
    QFrame *frameDirections;
    QRadioButton *radioButtonDirectionNorth;
    QRadioButton *radioButtonDirectionEast;
    QRadioButton *radioButtonDirectionSouth;
    QRadioButton *radioButtonDirectionWest;
    QLabel *labelDirection;
    QLabel *labelDirectionNorth;
    QLabel *labelDirectionEast;
    QLabel *labelDirectionSouth;
    QLabel *labelDirectionWest;
    QFrame *frameGroups;
    QRadioButton *radioButtonAgentGroup0;
    QRadioButton *radioButtonAgentGroup1;
    QRadioButton *radioButtonAgentGroup2;
    QRadioButton *radioButtonAgentGroup3;
    QLabel *labelGroups;
    QLabel *labelGroup0;
    QLabel *labelGroup1;
    QLabel *labelGroup2;
    QLabel *labelGroup3;
    QGroupBox *groupBox_3;
    QFrame *frame_2;
    QRadioButton *radioButtonShowGradient;
    QRadioButton *radioButtonShowAverageVelocity;
    QRadioButton *radioButtonShowPotential;
    QRadioButton *radioButtonShowDensity;
    QRadioButton *radioButtonShowSpeed;
    QRadioButton *radioButtonShowCost;
    QRadioButton *radioButtonShowDiscomfort;
    QLabel *mapAlphaLabelValue;
    QLabel *mapAlphaLabelName;
    QSlider *mapAlphaSlider;
    QLabel *gradientArrowsAlphaLabelValue;
    QSlider *gradientArrowsAlphaSlider;
    QLabel *gradientArrowsAlphaLabelName;
    QLabel *label_12;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QFrame *line_9;
    QFrame *line_10;
    QFrame *line_11;
    QFrame *line_12;
    QFrame *line_13;
    QLabel *label20;
    QFrame *line_14;
    QLabel *label20_2;
    QLabel *gradientInterpolateLabelName;
    QFrame *frame;
    QRadioButton *gradientInterpolateYes;
    QRadioButton *gradientInterpolateNo;
    QGroupBox *groupBox_8;
    QCheckBox *checkBoxIsDrawingSplatAreas;
    QCheckBox *isDrawingSprites;
    QGroupBox *groupBox_5;
    QLabel *workGroupsAlphaLabelValue;
    QLabel *workItemsAlphaLabelValue;
    QSlider *workItemsAlphaSlider;
    QLabel *workItemsAlphaLabelName;
    QSlider *workGroupsAlphaSlider;
    QLabel *workGroupsAlphaLabelName;
    QSlider *groupStatesAlphaSlider;
    QLabel *groupStatesAlphaLabelValue;
    QLabel *groupStatesAlphaLabelName;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *labelSelectiveUpdateState;
    QGroupBox *groupBox_2;
    QLabel *iterationsLabelValue;
    QLabel *iterationsLabelName;
    QSlider *iterationsSlider;
    QLabel *label_7;
    QLineEdit *innerLoopCountLineEdit;
    QLabel *label_8;
    QLabel *workItemIterations;
    QCheckBox *isBreakingAfterSolverStep;
    QLabel *label_21;
    QLabel *innerUnrollFactor;
    QGroupBox *groupBox_11;
    QRadioButton *isUpdatingAll;
    QRadioButton *isUpdatingSelectively;
    QGroupBox *groupBox_6;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lengthLineEdit;
    QLineEdit *timeLineEdit;
    QLineEdit *discomfortLineEdit;
    QGroupBox *groupBox_7;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *minimumDensityLineEdit;
    QLineEdit *maximumDensityLineEdit;
    QGroupBox *groupBox_12;
    QLineEdit *discomfortBrushRadiusLineEdit;
    QLabel *label_18;
    QLineEdit *discomfortBrushIntensityLineEdit;
    QLabel *label_20;
    QFrame *line_15;
    QLabel *label_16;
    QLabel *label_17;
    QGroupBox *groupBox;
    QLabel *label_6;
    QLineEdit *maximumSpeedLineEdit;
    QCheckBox *resolveCollisionsCheckBox;
    QRadioButton *exitPark;
    QRadioButton *exitChangeGroup;
    QRadioButton *exitRespawn;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QTextEdit *logWindow;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxPrintProfiling;
    QCheckBox *checkBoxProfileDetails;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QTextBrowser *profilingWindow;
    QTextBrowser *kernelProfilingWindow;
    QWidget *tab_7;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *memoryWindow;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *CrowdQtClass)
    {
        if (CrowdQtClass->objectName().isEmpty())
            CrowdQtClass->setObjectName(QString::fromUtf8("CrowdQtClass"));
        CrowdQtClass->resize(1280, 1024);
        CrowdQtClass->setMinimumSize(QSize(128, 128));
        CrowdQtClass->setContextMenuPolicy(Qt::NoContextMenu);
        CrowdQtClass->setDockNestingEnabled(true);
        actionExit = new QAction(CrowdQtClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionZoom_in = new QAction(CrowdQtClass);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        actionZoom_out = new QAction(CrowdQtClass);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        actionZoom_1_1 = new QAction(CrowdQtClass);
        actionZoom_1_1->setObjectName(QString::fromUtf8("actionZoom_1_1"));
        actionRewind = new QAction(CrowdQtClass);
        actionRewind->setObjectName(QString::fromUtf8("actionRewind"));
        actionPlay = new QAction(CrowdQtClass);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionPlay->setCheckable(true);
        actionStep = new QAction(CrowdQtClass);
        actionStep->setObjectName(QString::fromUtf8("actionStep"));
        actionAbout = new QAction(CrowdQtClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(CrowdQtClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new GraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(362, 0));
        scrollArea->setMaximumSize(QSize(362, 16777215));
        scrollArea->setFocusPolicy(Qt::NoFocus);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 342, 1369));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_10 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setMinimumSize(QSize(321, 180));
        groupBox_10->setMaximumSize(QSize(321, 180));
        frameLegendVector = new QFrame(groupBox_10);
        frameLegendVector->setObjectName(QString::fromUtf8("frameLegendVector"));
        frameLegendVector->setGeometry(QRect(10, 30, 191, 111));
        labelSouth = new QLabel(frameLegendVector);
        labelSouth->setObjectName(QString::fromUtf8("labelSouth"));
        labelSouth->setGeometry(QRect(110, 92, 16, 19));
        labelEast = new QLabel(frameLegendVector);
        labelEast->setObjectName(QString::fromUtf8("labelEast"));
        labelEast->setGeometry(QRect(150, 46, 16, 19));
        gradientLegendLabel = new QLabel(frameLegendVector);
        gradientLegendLabel->setObjectName(QString::fromUtf8("gradientLegendLabel"));
        gradientLegendLabel->setGeometry(QRect(80, 26, 64, 64));
        gradientLegendLabel->setMinimumSize(QSize(64, 64));
        gradientLegendLabel->setMaximumSize(QSize(64, 64));
        labelNorth = new QLabel(frameLegendVector);
        labelNorth->setObjectName(QString::fromUtf8("labelNorth"));
        labelNorth->setGeometry(QRect(106, 6, 16, 19));
        labelWest = new QLabel(frameLegendVector);
        labelWest->setObjectName(QString::fromUtf8("labelWest"));
        labelWest->setGeometry(QRect(60, 46, 21, 19));
        label_10 = new QLabel(frameLegendVector);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 0, 51, 31));
        frameLegendValue = new QFrame(groupBox_10);
        frameLegendValue->setObjectName(QString::fromUtf8("frameLegendValue"));
        frameLegendValue->setGeometry(QRect(0, 30, 221, 151));
        valueLegendLabel = new QLabel(frameLegendValue);
        valueLegendLabel->setObjectName(QString::fromUtf8("valueLegendLabel"));
        valueLegendLabel->setGeometry(QRect(96, 40, 51, 64));
        label_11 = new QLabel(frameLegendValue);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 0, 51, 31));
        colorScaleMaxLineEdit = new QLineEdit(frameLegendValue);
        colorScaleMaxLineEdit->setObjectName(QString::fromUtf8("colorScaleMaxLineEdit"));
        colorScaleMaxLineEdit->setGeometry(QRect(60, 0, 121, 29));
        colorScaleMaxLineEdit->setMaxLength(12);
        colorScaleMaxLineEdit->setAlignment(Qt::AlignCenter);
        colorScaleMinLineEdit = new QLineEdit(frameLegendValue);
        colorScaleMinLineEdit->setObjectName(QString::fromUtf8("colorScaleMinLineEdit"));
        colorScaleMinLineEdit->setGeometry(QRect(60, 120, 121, 29));
        colorScaleMinLineEdit->setMaxLength(12);
        colorScaleMinLineEdit->setAlignment(Qt::AlignCenter);
        valueLegendLabel->raise();
        label_11->raise();
        colorScaleMinLineEdit->raise();
        colorScaleMaxLineEdit->raise();
        label_9 = new QLabel(groupBox_10);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(220, 20, 101, 51));
        frameDirections = new QFrame(groupBox_10);
        frameDirections->setObjectName(QString::fromUtf8("frameDirections"));
        frameDirections->setGeometry(QRect(160, 100, 161, 91));
        frameDirections->setFrameShape(QFrame::NoFrame);
        frameDirections->setFrameShadow(QFrame::Raised);
        radioButtonDirectionNorth = new QRadioButton(frameDirections);
        radioButtonDirectionNorth->setObjectName(QString::fromUtf8("radioButtonDirectionNorth"));
        radioButtonDirectionNorth->setGeometry(QRect(120, 30, 16, 16));
        radioButtonDirectionNorth->setLayoutDirection(Qt::LeftToRight);
        radioButtonDirectionNorth->setChecked(true);
        radioButtonDirectionEast = new QRadioButton(frameDirections);
        radioButtonDirectionEast->setObjectName(QString::fromUtf8("radioButtonDirectionEast"));
        radioButtonDirectionEast->setGeometry(QRect(130, 40, 16, 16));
        radioButtonDirectionEast->setLayoutDirection(Qt::LeftToRight);
        radioButtonDirectionSouth = new QRadioButton(frameDirections);
        radioButtonDirectionSouth->setObjectName(QString::fromUtf8("radioButtonDirectionSouth"));
        radioButtonDirectionSouth->setGeometry(QRect(120, 50, 16, 16));
        radioButtonDirectionSouth->setLayoutDirection(Qt::LeftToRight);
        radioButtonDirectionWest = new QRadioButton(frameDirections);
        radioButtonDirectionWest->setObjectName(QString::fromUtf8("radioButtonDirectionWest"));
        radioButtonDirectionWest->setGeometry(QRect(110, 40, 16, 16));
        radioButtonDirectionWest->setLayoutDirection(Qt::LeftToRight);
        labelDirection = new QLabel(frameDirections);
        labelDirection->setObjectName(QString::fromUtf8("labelDirection"));
        labelDirection->setGeometry(QRect(60, 0, 75, 19));
        labelDirectionNorth = new QLabel(frameDirections);
        labelDirectionNorth->setObjectName(QString::fromUtf8("labelDirectionNorth"));
        labelDirectionNorth->setGeometry(QRect(123, 15, 16, 16));
        labelDirectionNorth->setAlignment(Qt::AlignCenter);
        labelDirectionEast = new QLabel(frameDirections);
        labelDirectionEast->setObjectName(QString::fromUtf8("labelDirectionEast"));
        labelDirectionEast->setGeometry(QRect(147, 40, 16, 16));
        labelDirectionEast->setAlignment(Qt::AlignCenter);
        labelDirectionSouth = new QLabel(frameDirections);
        labelDirectionSouth->setObjectName(QString::fromUtf8("labelDirectionSouth"));
        labelDirectionSouth->setGeometry(QRect(124, 66, 16, 16));
        labelDirectionSouth->setAlignment(Qt::AlignCenter);
        labelDirectionWest = new QLabel(frameDirections);
        labelDirectionWest->setObjectName(QString::fromUtf8("labelDirectionWest"));
        labelDirectionWest->setGeometry(QRect(96, 40, 16, 16));
        labelDirectionWest->setAlignment(Qt::AlignCenter);
        frameGroups = new QFrame(groupBox_10);
        frameGroups->setObjectName(QString::fromUtf8("frameGroups"));
        frameGroups->setGeometry(QRect(150, 120, 171, 61));
        frameGroups->setFrameShape(QFrame::NoFrame);
        frameGroups->setFrameShadow(QFrame::Raised);
        radioButtonAgentGroup0 = new QRadioButton(frameGroups);
        radioButtonAgentGroup0->setObjectName(QString::fromUtf8("radioButtonAgentGroup0"));
        radioButtonAgentGroup0->setGeometry(QRect(90, 20, 16, 24));
        radioButtonAgentGroup0->setLayoutDirection(Qt::LeftToRight);
        radioButtonAgentGroup0->setChecked(true);
        radioButtonAgentGroup1 = new QRadioButton(frameGroups);
        radioButtonAgentGroup1->setObjectName(QString::fromUtf8("radioButtonAgentGroup1"));
        radioButtonAgentGroup1->setGeometry(QRect(110, 20, 16, 24));
        radioButtonAgentGroup1->setLayoutDirection(Qt::LeftToRight);
        radioButtonAgentGroup2 = new QRadioButton(frameGroups);
        radioButtonAgentGroup2->setObjectName(QString::fromUtf8("radioButtonAgentGroup2"));
        radioButtonAgentGroup2->setGeometry(QRect(130, 20, 16, 24));
        radioButtonAgentGroup2->setLayoutDirection(Qt::LeftToRight);
        radioButtonAgentGroup3 = new QRadioButton(frameGroups);
        radioButtonAgentGroup3->setObjectName(QString::fromUtf8("radioButtonAgentGroup3"));
        radioButtonAgentGroup3->setGeometry(QRect(150, 20, 16, 24));
        radioButtonAgentGroup3->setLayoutDirection(Qt::LeftToRight);
        labelGroups = new QLabel(frameGroups);
        labelGroups->setObjectName(QString::fromUtf8("labelGroups"));
        labelGroups->setGeometry(QRect(70, 0, 161, 19));
        labelGroup0 = new QLabel(frameGroups);
        labelGroup0->setObjectName(QString::fromUtf8("labelGroup0"));
        labelGroup0->setGeometry(QRect(94, 40, 16, 16));
        labelGroup0->setAlignment(Qt::AlignCenter);
        labelGroup1 = new QLabel(frameGroups);
        labelGroup1->setObjectName(QString::fromUtf8("labelGroup1"));
        labelGroup1->setGeometry(QRect(115, 40, 16, 16));
        labelGroup1->setAlignment(Qt::AlignCenter);
        labelGroup2 = new QLabel(frameGroups);
        labelGroup2->setObjectName(QString::fromUtf8("labelGroup2"));
        labelGroup2->setGeometry(QRect(135, 40, 16, 16));
        labelGroup2->setAlignment(Qt::AlignCenter);
        labelGroup3 = new QLabel(frameGroups);
        labelGroup3->setObjectName(QString::fromUtf8("labelGroup3"));
        labelGroup3->setGeometry(QRect(156, 40, 16, 16));
        labelGroup3->setAlignment(Qt::AlignCenter);
        labelGroups->raise();
        labelGroup0->raise();
        labelGroup1->raise();
        labelGroup2->raise();
        labelGroup3->raise();
        radioButtonAgentGroup1->raise();
        radioButtonAgentGroup2->raise();
        radioButtonAgentGroup0->raise();
        radioButtonAgentGroup3->raise();

        gridLayout_3->addWidget(groupBox_10, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(321, 260));
        groupBox_3->setMaximumSize(QSize(321, 260));
        frame_2 = new QFrame(groupBox_3);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(-10, 20, 341, 231));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        radioButtonShowGradient = new QRadioButton(frame_2);
        radioButtonShowGradient->setObjectName(QString::fromUtf8("radioButtonShowGradient"));
        radioButtonShowGradient->setGeometry(QRect(20, 130, 171, 21));
        radioButtonShowGradient->setMinimumSize(QSize(100, 0));
        radioButtonShowGradient->setChecked(false);
        radioButtonShowAverageVelocity = new QRadioButton(frame_2);
        radioButtonShowAverageVelocity->setObjectName(QString::fromUtf8("radioButtonShowAverageVelocity"));
        radioButtonShowAverageVelocity->setGeometry(QRect(20, 50, 241, 24));
        radioButtonShowAverageVelocity->setMinimumSize(QSize(200, 0));
        radioButtonShowAverageVelocity->setChecked(false);
        radioButtonShowPotential = new QRadioButton(frame_2);
        radioButtonShowPotential->setObjectName(QString::fromUtf8("radioButtonShowPotential"));
        radioButtonShowPotential->setGeometry(QRect(20, 110, 101, 24));
        radioButtonShowPotential->setMinimumSize(QSize(100, 0));
        radioButtonShowPotential->setChecked(false);
        radioButtonShowDensity = new QRadioButton(frame_2);
        radioButtonShowDensity->setObjectName(QString::fromUtf8("radioButtonShowDensity"));
        radioButtonShowDensity->setGeometry(QRect(20, 30, 101, 24));
        radioButtonShowDensity->setMinimumSize(QSize(100, 0));
        radioButtonShowDensity->setChecked(false);
        radioButtonShowSpeed = new QRadioButton(frame_2);
        radioButtonShowSpeed->setObjectName(QString::fromUtf8("radioButtonShowSpeed"));
        radioButtonShowSpeed->setGeometry(QRect(20, 70, 100, 24));
        radioButtonShowSpeed->setMinimumSize(QSize(100, 0));
        radioButtonShowSpeed->setChecked(false);
        radioButtonShowCost = new QRadioButton(frame_2);
        radioButtonShowCost->setObjectName(QString::fromUtf8("radioButtonShowCost"));
        radioButtonShowCost->setGeometry(QRect(20, 90, 100, 24));
        radioButtonShowCost->setMinimumSize(QSize(100, 0));
        radioButtonShowCost->setChecked(false);
        radioButtonShowDiscomfort = new QRadioButton(frame_2);
        radioButtonShowDiscomfort->setObjectName(QString::fromUtf8("radioButtonShowDiscomfort"));
        radioButtonShowDiscomfort->setGeometry(QRect(20, 10, 200, 24));
        radioButtonShowDiscomfort->setMinimumSize(QSize(100, 0));
        radioButtonShowDiscomfort->setChecked(true);
        mapAlphaLabelValue = new QLabel(frame_2);
        mapAlphaLabelValue->setObjectName(QString::fromUtf8("mapAlphaLabelValue"));
        mapAlphaLabelValue->setGeometry(QRect(290, 210, 40, 19));
        mapAlphaLabelValue->setMinimumSize(QSize(40, 0));
        mapAlphaLabelValue->setMaximumSize(QSize(60, 16777215));
        mapAlphaLabelValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        mapAlphaLabelName = new QLabel(frame_2);
        mapAlphaLabelName->setObjectName(QString::fromUtf8("mapAlphaLabelName"));
        mapAlphaLabelName->setGeometry(QRect(170, 210, 61, 19));
        mapAlphaSlider = new QSlider(frame_2);
        mapAlphaSlider->setObjectName(QString::fromUtf8("mapAlphaSlider"));
        mapAlphaSlider->setGeometry(QRect(220, 210, 71, 24));
        mapAlphaSlider->setMinimum(0);
        mapAlphaSlider->setMaximum(100);
        mapAlphaSlider->setValue(100);
        mapAlphaSlider->setOrientation(Qt::Horizontal);
        gradientArrowsAlphaLabelValue = new QLabel(frame_2);
        gradientArrowsAlphaLabelValue->setObjectName(QString::fromUtf8("gradientArrowsAlphaLabelValue"));
        gradientArrowsAlphaLabelValue->setGeometry(QRect(290, 150, 40, 19));
        gradientArrowsAlphaLabelValue->setMinimumSize(QSize(40, 0));
        gradientArrowsAlphaLabelValue->setMaximumSize(QSize(60, 16777215));
        gradientArrowsAlphaLabelValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gradientArrowsAlphaSlider = new QSlider(frame_2);
        gradientArrowsAlphaSlider->setObjectName(QString::fromUtf8("gradientArrowsAlphaSlider"));
        gradientArrowsAlphaSlider->setGeometry(QRect(220, 150, 71, 24));
        gradientArrowsAlphaSlider->setMinimum(0);
        gradientArrowsAlphaSlider->setMaximum(100);
        gradientArrowsAlphaSlider->setValue(0);
        gradientArrowsAlphaSlider->setOrientation(Qt::Horizontal);
        gradientArrowsAlphaLabelName = new QLabel(frame_2);
        gradientArrowsAlphaLabelName->setObjectName(QString::fromUtf8("gradientArrowsAlphaLabelName"));
        gradientArrowsAlphaLabelName->setGeometry(QRect(130, 150, 91, 31));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 210, 75, 19));
        line = new QFrame(frame_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(220, 120, 16, 20));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);
        line_2 = new QFrame(frame_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(212, 120, 16, 21));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setFrameShape(QFrame::VLine);
        line_3 = new QFrame(frame_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(303, -1, 16, 131));
        line_3->setFrameShadow(QFrame::Plain);
        line_3->setFrameShape(QFrame::VLine);
        line_4 = new QFrame(frame_2);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(129, 110, 91, 20));
        line_4->setFrameShadow(QFrame::Plain);
        line_4->setFrameShape(QFrame::HLine);
        line_5 = new QFrame(frame_2);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(200, 130, 20, 20));
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setFrameShape(QFrame::HLine);
        line_6 = new QFrame(frame_2);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(128, 80, 20, 20));
        line_6->setFrameShadow(QFrame::Plain);
        line_6->setFrameShape(QFrame::HLine);
        line_7 = new QFrame(frame_2);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(108, 90, 20, 20));
        line_7->setFrameShadow(QFrame::Plain);
        line_7->setFrameShape(QFrame::HLine);
        line_8 = new QFrame(frame_2);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setGeometry(QRect(108, 70, 20, 20));
        line_8->setFrameShadow(QFrame::Plain);
        line_8->setFrameShape(QFrame::HLine);
        line_9 = new QFrame(frame_2);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setGeometry(QRect(120, 80, 16, 21));
        line_9->setFrameShadow(QFrame::Plain);
        line_9->setFrameShape(QFrame::VLine);
        line_10 = new QFrame(frame_2);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setGeometry(QRect(288, 0, 16, 91));
        line_10->setFrameShadow(QFrame::Plain);
        line_10->setFrameShape(QFrame::VLine);
        line_11 = new QFrame(frame_2);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setGeometry(QRect(200, 136, 61, 20));
        line_11->setFrameShadow(QFrame::Plain);
        line_11->setFrameShape(QFrame::HLine);
        line_12 = new QFrame(frame_2);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setGeometry(QRect(253, 146, 16, 6));
        line_12->setFrameShadow(QFrame::Plain);
        line_12->setFrameShape(QFrame::VLine);
        line_13 = new QFrame(frame_2);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setGeometry(QRect(234, 80, 63, 20));
        line_13->setFrameShadow(QFrame::Plain);
        line_13->setFrameShape(QFrame::HLine);
        label20 = new QLabel(frame_2);
        label20->setObjectName(QString::fromUtf8("label20"));
        label20->setEnabled(false);
        label20->setGeometry(QRect(154, 74, 71, 31));
        line_14 = new QFrame(frame_2);
        line_14->setObjectName(QString::fromUtf8("line_14"));
        line_14->setGeometry(QRect(300, 120, 12, 20));
        line_14->setFrameShadow(QFrame::Plain);
        line_14->setFrameShape(QFrame::HLine);
        label20_2 = new QLabel(frame_2);
        label20_2->setObjectName(QString::fromUtf8("label20_2"));
        label20_2->setEnabled(false);
        label20_2->setGeometry(QRect(240, 114, 61, 31));
        gradientInterpolateLabelName = new QLabel(frame_2);
        gradientInterpolateLabelName->setObjectName(QString::fromUtf8("gradientInterpolateLabelName"));
        gradientInterpolateLabelName->setGeometry(QRect(120, 180, 41, 21));
        frame = new QFrame(frame_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(160, 180, 171, 21));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        gradientInterpolateYes = new QRadioButton(frame);
        gradientInterpolateYes->setObjectName(QString::fromUtf8("gradientInterpolateYes"));
        gradientInterpolateYes->setGeometry(QRect(0, 0, 91, 23));
        gradientInterpolateYes->setChecked(false);
        gradientInterpolateNo = new QRadioButton(frame);
        gradientInterpolateNo->setObjectName(QString::fromUtf8("gradientInterpolateNo"));
        gradientInterpolateNo->setGeometry(QRect(80, 0, 91, 23));
        gradientInterpolateNo->setChecked(true);

        gridLayout_3->addWidget(groupBox_3, 3, 0, 1, 1);

        groupBox_8 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setMinimumSize(QSize(321, 60));
        groupBox_8->setMaximumSize(QSize(321, 60));
        checkBoxIsDrawingSplatAreas = new QCheckBox(groupBox_8);
        checkBoxIsDrawingSplatAreas->setObjectName(QString::fromUtf8("checkBoxIsDrawingSplatAreas"));
        checkBoxIsDrawingSplatAreas->setGeometry(QRect(160, 30, 131, 24));
        isDrawingSprites = new QCheckBox(groupBox_8);
        isDrawingSprites->setObjectName(QString::fromUtf8("isDrawingSprites"));
        isDrawingSprites->setGeometry(QRect(10, 30, 81, 24));
        isDrawingSprites->setChecked(true);

        gridLayout_3->addWidget(groupBox_8, 5, 0, 1, 1);

        groupBox_5 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(321, 140));
        groupBox_5->setMaximumSize(QSize(321, 140));
        workGroupsAlphaLabelValue = new QLabel(groupBox_5);
        workGroupsAlphaLabelValue->setObjectName(QString::fromUtf8("workGroupsAlphaLabelValue"));
        workGroupsAlphaLabelValue->setGeometry(QRect(280, 30, 40, 19));
        workGroupsAlphaLabelValue->setMinimumSize(QSize(40, 0));
        workGroupsAlphaLabelValue->setMaximumSize(QSize(60, 16777215));
        workGroupsAlphaLabelValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        workItemsAlphaLabelValue = new QLabel(groupBox_5);
        workItemsAlphaLabelValue->setObjectName(QString::fromUtf8("workItemsAlphaLabelValue"));
        workItemsAlphaLabelValue->setGeometry(QRect(280, 50, 40, 19));
        workItemsAlphaLabelValue->setMinimumSize(QSize(40, 0));
        workItemsAlphaLabelValue->setMaximumSize(QSize(60, 16777215));
        workItemsAlphaLabelValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        workItemsAlphaSlider = new QSlider(groupBox_5);
        workItemsAlphaSlider->setObjectName(QString::fromUtf8("workItemsAlphaSlider"));
        workItemsAlphaSlider->setGeometry(QRect(210, 50, 71, 24));
        workItemsAlphaSlider->setMinimum(0);
        workItemsAlphaSlider->setMaximum(100);
        workItemsAlphaSlider->setValue(0);
        workItemsAlphaSlider->setOrientation(Qt::Horizontal);
        workItemsAlphaLabelName = new QLabel(groupBox_5);
        workItemsAlphaLabelName->setObjectName(QString::fromUtf8("workItemsAlphaLabelName"));
        workItemsAlphaLabelName->setGeometry(QRect(160, 50, 61, 19));
        workGroupsAlphaSlider = new QSlider(groupBox_5);
        workGroupsAlphaSlider->setObjectName(QString::fromUtf8("workGroupsAlphaSlider"));
        workGroupsAlphaSlider->setGeometry(QRect(210, 30, 71, 24));
        workGroupsAlphaSlider->setMinimum(0);
        workGroupsAlphaSlider->setMaximum(100);
        workGroupsAlphaSlider->setValue(0);
        workGroupsAlphaSlider->setOrientation(Qt::Horizontal);
        workGroupsAlphaLabelName = new QLabel(groupBox_5);
        workGroupsAlphaLabelName->setObjectName(QString::fromUtf8("workGroupsAlphaLabelName"));
        workGroupsAlphaLabelName->setGeometry(QRect(160, 30, 61, 19));
        groupStatesAlphaSlider = new QSlider(groupBox_5);
        groupStatesAlphaSlider->setObjectName(QString::fromUtf8("groupStatesAlphaSlider"));
        groupStatesAlphaSlider->setGeometry(QRect(210, 80, 71, 24));
        groupStatesAlphaSlider->setMinimum(0);
        groupStatesAlphaSlider->setMaximum(100);
        groupStatesAlphaSlider->setValue(0);
        groupStatesAlphaSlider->setOrientation(Qt::Horizontal);
        groupStatesAlphaLabelValue = new QLabel(groupBox_5);
        groupStatesAlphaLabelValue->setObjectName(QString::fromUtf8("groupStatesAlphaLabelValue"));
        groupStatesAlphaLabelValue->setGeometry(QRect(280, 80, 40, 19));
        groupStatesAlphaLabelValue->setMinimumSize(QSize(40, 0));
        groupStatesAlphaLabelValue->setMaximumSize(QSize(60, 16777215));
        groupStatesAlphaLabelValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupStatesAlphaLabelName = new QLabel(groupBox_5);
        groupStatesAlphaLabelName->setObjectName(QString::fromUtf8("groupStatesAlphaLabelName"));
        groupStatesAlphaLabelName->setGeometry(QRect(160, 80, 61, 19));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 30, 111, 19));
        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 50, 101, 19));
        labelSelectiveUpdateState = new QLabel(groupBox_5);
        labelSelectiveUpdateState->setObjectName(QString::fromUtf8("labelSelectiveUpdateState"));
        labelSelectiveUpdateState->setGeometry(QRect(10, 78, 141, 41));

        gridLayout_3->addWidget(groupBox_5, 6, 0, 1, 1);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(321, 180));
        groupBox_2->setMaximumSize(QSize(321, 180));
        iterationsLabelValue = new QLabel(groupBox_2);
        iterationsLabelValue->setObjectName(QString::fromUtf8("iterationsLabelValue"));
        iterationsLabelValue->setGeometry(QRect(280, 30, 41, 19));
        iterationsLabelValue->setMinimumSize(QSize(40, 0));
        iterationsLabelValue->setMaximumSize(QSize(60, 16777215));
        iterationsLabelValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        iterationsLabelName = new QLabel(groupBox_2);
        iterationsLabelName->setObjectName(QString::fromUtf8("iterationsLabelName"));
        iterationsLabelName->setGeometry(QRect(10, 30, 101, 19));
        iterationsSlider = new QSlider(groupBox_2);
        iterationsSlider->setObjectName(QString::fromUtf8("iterationsSlider"));
        iterationsSlider->setGeometry(QRect(120, 30, 151, 24));
        iterationsSlider->setMinimum(1);
        iterationsSlider->setMaximum(200);
        iterationsSlider->setValue(75);
        iterationsSlider->setOrientation(Qt::Horizontal);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 60, 91, 19));
        innerLoopCountLineEdit = new QLineEdit(groupBox_2);
        innerLoopCountLineEdit->setObjectName(QString::fromUtf8("innerLoopCountLineEdit"));
        innerLoopCountLineEdit->setGeometry(QRect(250, 54, 71, 29));
        innerLoopCountLineEdit->setInputMask(QString::fromUtf8(""));
        innerLoopCountLineEdit->setText(QString::fromUtf8("10"));
        innerLoopCountLineEdit->setMaxLength(6);
        innerLoopCountLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(40, 120, 271, 20));
        QFont font;
        font.setPointSize(10);
        label_8->setFont(font);
        workItemIterations = new QLabel(groupBox_2);
        workItemIterations->setObjectName(QString::fromUtf8("workItemIterations"));
        workItemIterations->setGeometry(QRect(240, 120, 81, 19));
        workItemIterations->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        isBreakingAfterSolverStep = new QCheckBox(groupBox_2);
        isBreakingAfterSolverStep->setObjectName(QString::fromUtf8("isBreakingAfterSolverStep"));
        isBreakingAfterSolverStep->setGeometry(QRect(10, 150, 311, 24));
        isBreakingAfterSolverStep->setChecked(false);
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 90, 151, 19));
        innerUnrollFactor = new QLabel(groupBox_2);
        innerUnrollFactor->setObjectName(QString::fromUtf8("innerUnrollFactor"));
        innerUnrollFactor->setGeometry(QRect(230, 90, 91, 19));
        innerUnrollFactor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8->raise();
        iterationsLabelValue->raise();
        iterationsLabelName->raise();
        iterationsSlider->raise();
        label_7->raise();
        innerLoopCountLineEdit->raise();
        workItemIterations->raise();
        isBreakingAfterSolverStep->raise();
        label_21->raise();
        innerUnrollFactor->raise();

        gridLayout_3->addWidget(groupBox_2, 10, 0, 1, 1);

        groupBox_11 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setMinimumSize(QSize(321, 60));
        groupBox_11->setMaximumSize(QSize(321, 60));
        isUpdatingAll = new QRadioButton(groupBox_11);
        isUpdatingAll->setObjectName(QString::fromUtf8("isUpdatingAll"));
        isUpdatingAll->setGeometry(QRect(10, 30, 126, 24));
        isUpdatingAll->setChecked(false);
        isUpdatingSelectively = new QRadioButton(groupBox_11);
        isUpdatingSelectively->setObjectName(QString::fromUtf8("isUpdatingSelectively"));
        isUpdatingSelectively->setGeometry(QRect(160, 30, 171, 24));
        isUpdatingSelectively->setChecked(true);

        gridLayout_3->addWidget(groupBox_11, 11, 0, 1, 1);

        groupBox_6 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(321, 120));
        groupBox_6->setMaximumSize(QSize(321, 120));
        label = new QLabel(groupBox_6);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 35, 131, 19));
        label_2 = new QLabel(groupBox_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 65, 111, 19));
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 95, 131, 19));
        lengthLineEdit = new QLineEdit(groupBox_6);
        lengthLineEdit->setObjectName(QString::fromUtf8("lengthLineEdit"));
        lengthLineEdit->setGeometry(QRect(170, 30, 151, 29));
        lengthLineEdit->setInputMask(QString::fromUtf8(""));
        lengthLineEdit->setText(QString::fromUtf8("1.0"));
        lengthLineEdit->setMaxLength(12);
        lengthLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        timeLineEdit = new QLineEdit(groupBox_6);
        timeLineEdit->setObjectName(QString::fromUtf8("timeLineEdit"));
        timeLineEdit->setGeometry(QRect(170, 60, 151, 29));
        timeLineEdit->setInputMask(QString::fromUtf8(""));
        timeLineEdit->setText(QString::fromUtf8("1.0"));
        timeLineEdit->setMaxLength(12);
        timeLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        discomfortLineEdit = new QLineEdit(groupBox_6);
        discomfortLineEdit->setObjectName(QString::fromUtf8("discomfortLineEdit"));
        discomfortLineEdit->setGeometry(QRect(170, 90, 151, 29));
        discomfortLineEdit->setInputMask(QString::fromUtf8(""));
        discomfortLineEdit->setText(QString::fromUtf8("1.0"));
        discomfortLineEdit->setMaxLength(12);
        discomfortLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(groupBox_6, 12, 0, 1, 1);

        groupBox_7 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setMinimumSize(QSize(321, 60));
        groupBox_7->setMaximumSize(QSize(321, 60));
        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 30, 91, 19));
        label_5 = new QLabel(groupBox_7);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(170, 30, 101, 19));
        minimumDensityLineEdit = new QLineEdit(groupBox_7);
        minimumDensityLineEdit->setObjectName(QString::fromUtf8("minimumDensityLineEdit"));
        minimumDensityLineEdit->setGeometry(QRect(90, 30, 71, 29));
        minimumDensityLineEdit->setInputMask(QString::fromUtf8(""));
        minimumDensityLineEdit->setText(QString::fromUtf8("0.5"));
        minimumDensityLineEdit->setMaxLength(12);
        minimumDensityLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        maximumDensityLineEdit = new QLineEdit(groupBox_7);
        maximumDensityLineEdit->setObjectName(QString::fromUtf8("maximumDensityLineEdit"));
        maximumDensityLineEdit->setGeometry(QRect(250, 30, 71, 29));
        maximumDensityLineEdit->setInputMask(QString::fromUtf8(""));
        maximumDensityLineEdit->setText(QString::fromUtf8("0.8"));
        maximumDensityLineEdit->setMaxLength(12);
        maximumDensityLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(groupBox_7, 14, 0, 1, 1);

        groupBox_12 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setMinimumSize(QSize(321, 60));
        groupBox_12->setMaximumSize(QSize(321, 60));
        discomfortBrushRadiusLineEdit = new QLineEdit(groupBox_12);
        discomfortBrushRadiusLineEdit->setObjectName(QString::fromUtf8("discomfortBrushRadiusLineEdit"));
        discomfortBrushRadiusLineEdit->setGeometry(QRect(90, 30, 71, 29));
        discomfortBrushRadiusLineEdit->setInputMask(QString::fromUtf8(""));
        discomfortBrushRadiusLineEdit->setText(QString::fromUtf8("10.0"));
        discomfortBrushRadiusLineEdit->setMaxLength(12);
        discomfortBrushRadiusLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_18 = new QLabel(groupBox_12);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 30, 71, 19));
        discomfortBrushIntensityLineEdit = new QLineEdit(groupBox_12);
        discomfortBrushIntensityLineEdit->setObjectName(QString::fromUtf8("discomfortBrushIntensityLineEdit"));
        discomfortBrushIntensityLineEdit->setGeometry(QRect(250, 30, 71, 29));
        discomfortBrushIntensityLineEdit->setInputMask(QString::fromUtf8(""));
        discomfortBrushIntensityLineEdit->setText(QString::fromUtf8("0.0"));
        discomfortBrushIntensityLineEdit->setMaxLength(12);
        discomfortBrushIntensityLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_20 = new QLabel(groupBox_12);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(170, 30, 71, 19));

        gridLayout_3->addWidget(groupBox_12, 16, 0, 1, 1);

        line_15 = new QFrame(scrollAreaWidgetContents);
        line_15->setObjectName(QString::fromUtf8("line_15"));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_15, 7, 0, 1, 1);

        label_16 = new QLabel(scrollAreaWidgetContents);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QFont font1;
        font1.setBold(false);
        font1.setItalic(true);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        label_16->setFont(font1);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_16, 0, 0, 1, 1);

        label_17 = new QLabel(scrollAreaWidgetContents);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font1);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_17, 8, 0, 1, 1);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(321, 120));
        groupBox->setMaximumSize(QSize(321, 120));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 30, 121, 18));
        maximumSpeedLineEdit = new QLineEdit(groupBox);
        maximumSpeedLineEdit->setObjectName(QString::fromUtf8("maximumSpeedLineEdit"));
        maximumSpeedLineEdit->setGeometry(QRect(170, 30, 150, 29));
        maximumSpeedLineEdit->setInputMask(QString::fromUtf8(""));
        maximumSpeedLineEdit->setText(QString::fromUtf8("12.0"));
        maximumSpeedLineEdit->setMaxLength(5);
        maximumSpeedLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        resolveCollisionsCheckBox = new QCheckBox(groupBox);
        resolveCollisionsCheckBox->setObjectName(QString::fromUtf8("resolveCollisionsCheckBox"));
        resolveCollisionsCheckBox->setGeometry(QRect(10, 60, 191, 24));
        resolveCollisionsCheckBox->setChecked(true);
        exitPark = new QRadioButton(groupBox);
        exitPark->setObjectName(QString::fromUtf8("exitPark"));
        exitPark->setGeometry(QRect(10, 90, 61, 23));
        exitPark->setChecked(true);
        exitChangeGroup = new QRadioButton(groupBox);
        exitChangeGroup->setObjectName(QString::fromUtf8("exitChangeGroup"));
        exitChangeGroup->setGeometry(QRect(80, 90, 131, 23));
        exitRespawn = new QRadioButton(groupBox);
        exitRespawn->setObjectName(QString::fromUtf8("exitRespawn"));
        exitRespawn->setGeometry(QRect(220, 90, 101, 23));

        gridLayout_3->addWidget(groupBox, 17, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);

        CrowdQtClass->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(CrowdQtClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CrowdQtClass->setStatusBar(statusbar);
        toolBar = new QToolBar(CrowdQtClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        CrowdQtClass->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget = new QDockWidget(CrowdQtClass);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_4 = new QGridLayout(dockWidgetContents);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        logWindow = new QTextEdit(tab);
        logWindow->setObjectName(QString::fromUtf8("logWindow"));
        logWindow->setUndoRedoEnabled(false);
        logWindow->setLineWrapMode(QTextEdit::NoWrap);
        logWindow->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout->addWidget(logWindow);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_5 = new QHBoxLayout(tab_2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBoxPrintProfiling = new QCheckBox(tab_2);
        checkBoxPrintProfiling->setObjectName(QString::fromUtf8("checkBoxPrintProfiling"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBoxPrintProfiling->sizePolicy().hasHeightForWidth());
        checkBoxPrintProfiling->setSizePolicy(sizePolicy1);
        checkBoxPrintProfiling->setChecked(true);

        horizontalLayout_3->addWidget(checkBoxPrintProfiling);

        checkBoxProfileDetails = new QCheckBox(tab_2);
        checkBoxProfileDetails->setObjectName(QString::fromUtf8("checkBoxProfileDetails"));
        sizePolicy1.setHeightForWidth(checkBoxProfileDetails->sizePolicy().hasHeightForWidth());
        checkBoxProfileDetails->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(checkBoxProfileDetails);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        profilingWindow = new QTextBrowser(tab_2);
        profilingWindow->setObjectName(QString::fromUtf8("profilingWindow"));
        profilingWindow->setMinimumSize(QSize(0, 0));
        profilingWindow->setDocumentTitle(QString::fromUtf8(""));
        profilingWindow->setLineWrapMode(QTextEdit::NoWrap);
        profilingWindow->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px;"
                        " margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><"
                        "/p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; m"
                        "argin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -"
                        "qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt"
                        ";\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; "
                        "text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p sty"
                        "le=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; marg"
                        "in-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; fo"
                        "nt-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-"
                        "type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin"
                        "-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; f"
                        "ont-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-"
                        "top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-blo"
                        "ck-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></"
                        "p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bot"
                        "tom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-i"
                        "ndent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-"
                        "qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p></td></tr></table></body></html>"));
        profilingWindow->setAcceptRichText(false);
        profilingWindow->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        profilingWindow->setOpenLinks(false);

        horizontalLayout_4->addWidget(profilingWindow);

        kernelProfilingWindow = new QTextBrowser(tab_2);
        kernelProfilingWindow->setObjectName(QString::fromUtf8("kernelProfilingWindow"));
        kernelProfilingWindow->setDocumentTitle(QString::fromUtf8(""));
        kernelProfilingWindow->setLineWrapMode(QTextEdit::NoWrap);
        kernelProfilingWindow->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px;"
                        " margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><"
                        "/p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; ma"
                        "rgin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; "
                        "font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragrap"
                        "h-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; marg"
                        "in-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans';"
                        " font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margi"
                        "n-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-b"
                        "lock-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\">"
                        "</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-b"
                        "ottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text"
                        "-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\""
                        "-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-le"
                        "ft:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-fa"
                        "mily:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:"
                        "empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-righ"
                        "t:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-s"
                        "ize:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0"
                        "px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p></td></tr></table></body></html>"));
        kernelProfilingWindow->setAcceptRichText(false);
        kernelProfilingWindow->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        kernelProfilingWindow->setOpenLinks(false);

        horizontalLayout_4->addWidget(kernelProfilingWindow);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);

        tabWidget->addTab(tab_2, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        horizontalLayout_2 = new QHBoxLayout(tab_7);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        memoryWindow = new QTextBrowser(tab_7);
        memoryWindow->setObjectName(QString::fromUtf8("memoryWindow"));
        memoryWindow->setDocumentTitle(QString::fromUtf8(""));
        memoryWindow->setLineWrapMode(QTextEdit::NoWrap);
        memoryWindow->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px;"
                        " margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><"
                        "/p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt"
                        "-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\""
                        "></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-"
                        "bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; tex"
                        "t-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style="
                        "\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-"
                        "left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-"
                        "family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-typ"
                        "e:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-ri"
                        "ght:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font"
                        "-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top"
                        ":0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-"
                        "indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
""
                        "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px"
                        "; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0"
                        "px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-para"
                        "graph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; "
                        "margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sa"
                        "ns'; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans'; font-size:12pt;\"></p></td></tr></table></body></html>"));
        memoryWindow->setAcceptRichText(false);
        memoryWindow->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        memoryWindow->setOpenLinks(false);

        horizontalLayout_2->addWidget(memoryWindow);

        tabWidget->addTab(tab_7, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        CrowdQtClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget);
        menuBar = new QMenuBar(CrowdQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        CrowdQtClass->setMenuBar(menuBar);

        toolBar->addAction(actionRewind);
        toolBar->addAction(actionPlay);
        toolBar->addAction(actionStep);
        toolBar->addSeparator();
        toolBar->addAction(actionZoom_out);
        toolBar->addAction(actionZoom_1_1);
        toolBar->addAction(actionZoom_in);
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(CrowdQtClass);
        QObject::connect(actionExit, SIGNAL(activated()), CrowdQtClass, SLOT(close()));
        QObject::connect(actionZoom_in, SIGNAL(activated()), graphicsView, SLOT(zoomIn()));
        QObject::connect(actionZoom_out, SIGNAL(activated()), graphicsView, SLOT(zoomOut()));
        QObject::connect(actionZoom_1_1, SIGNAL(activated()), graphicsView, SLOT(zoomOriginal()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CrowdQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *CrowdQtClass)
    {
        CrowdQtClass->setWindowTitle(QApplication::translate("CrowdQtClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("CrowdQtClass", "Quit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("CrowdQtClass", "Quit application\n"
"[ESC]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("CrowdQtClass", "Quit application [ESC]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionExit->setShortcut(QApplication::translate("CrowdQtClass", "Esc", 0, QApplication::UnicodeUTF8));
        actionZoom_in->setText(QApplication::translate("CrowdQtClass", "Zoom in", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionZoom_in->setToolTip(QApplication::translate("CrowdQtClass", "Zoom in\n"
"[+ or mouse wheel]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionZoom_in->setStatusTip(QApplication::translate("CrowdQtClass", "Zoom in [+ or mouse wheel]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoom_in->setShortcut(QApplication::translate("CrowdQtClass", "+", 0, QApplication::UnicodeUTF8));
        actionZoom_out->setText(QApplication::translate("CrowdQtClass", "Zoom out", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionZoom_out->setToolTip(QApplication::translate("CrowdQtClass", "Zoom out\n"
"[- or mouse wheel]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionZoom_out->setStatusTip(QApplication::translate("CrowdQtClass", "Zoom out [- or mouse wheel]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoom_out->setShortcut(QApplication::translate("CrowdQtClass", "-", 0, QApplication::UnicodeUTF8));
        actionZoom_1_1->setText(QApplication::translate("CrowdQtClass", "Zoom original", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionZoom_1_1->setToolTip(QApplication::translate("CrowdQtClass", "Zoom original\n"
"[*]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionZoom_1_1->setStatusTip(QApplication::translate("CrowdQtClass", "Zoom original [*]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoom_1_1->setShortcut(QApplication::translate("CrowdQtClass", "*", 0, QApplication::UnicodeUTF8));
        actionRewind->setText(QApplication::translate("CrowdQtClass", "Rewind", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRewind->setToolTip(QApplication::translate("CrowdQtClass", "Reset agent positions to start\n"
"[Backspace]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRewind->setStatusTip(QApplication::translate("CrowdQtClass", "Reset agent positions to start [Backspace]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionRewind->setShortcut(QApplication::translate("CrowdQtClass", "Backspace", 0, QApplication::UnicodeUTF8));
        actionPlay->setText(QApplication::translate("CrowdQtClass", "Play", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPlay->setToolTip(QApplication::translate("CrowdQtClass", "Continuously step simulation\n"
"[Space]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPlay->setStatusTip(QApplication::translate("CrowdQtClass", "Continuously step simulation [Space]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPlay->setShortcut(QApplication::translate("CrowdQtClass", "Space", 0, QApplication::UnicodeUTF8));
        actionStep->setText(QApplication::translate("CrowdQtClass", "Step", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionStep->setToolTip(QApplication::translate("CrowdQtClass", "Single step simulation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionStep->setStatusTip(QApplication::translate("CrowdQtClass", "Single step simulation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAbout->setText(QApplication::translate("CrowdQtClass", "About", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("CrowdQtClass", "Show info about this application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_10->setTitle(QApplication::translate("CrowdQtClass", "Legend", 0, QApplication::UnicodeUTF8));
        labelSouth->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">S</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        labelEast->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">E</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        gradientLegendLabel->setToolTip(QApplication::translate("CrowdQtClass", "Color scale for vector fields.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        gradientLegendLabel->setStatusTip(QApplication::translate("CrowdQtClass", "Color scale for vector fields.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        gradientLegendLabel->setText(QString());
        labelNorth->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">N</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        labelWest->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">W</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt;\">Vector</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt;\">Field</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        valueLegendLabel->setToolTip(QApplication::translate("CrowdQtClass", "Color scale for scalar fields.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        valueLegendLabel->setStatusTip(QApplication::translate("CrowdQtClass", "Color scale for scalar fields.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        valueLegendLabel->setText(QString());
        label_11->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt;\">Scalar</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt;\">Field</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        colorScaleMaxLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Color scale's upper bound\n"
"[Shift + Left Mouse Button] to select in view.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        colorScaleMaxLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Color scale's upper bound. [Shift + Left Mouse Button] to select in view.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        colorScaleMaxLineEdit->setText(QApplication::translate("CrowdQtClass", "n/a", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        colorScaleMinLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Color scale's lower bound. [Ctrl + Left Mouse Button] to select in view.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        colorScaleMinLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Color scale's lower bound. [Ctrl + Left Mouse Button] to select in view.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        colorScaleMinLineEdit->setText(QApplication::translate("CrowdQtClass", "n/a", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">White  - Infinity</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Purple - NaN</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        radioButtonDirectionNorth->setText(QString());
#ifndef QT_NO_TOOLTIP
        radioButtonDirectionEast->setToolTip(QApplication::translate("CrowdQtClass", "Show ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButtonDirectionEast->setText(QString());
        radioButtonDirectionSouth->setText(QString());
        radioButtonDirectionWest->setText(QString());
        labelDirection->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Direction</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDirectionNorth->setToolTip(QApplication::translate("CrowdQtClass", "Show values for direction north.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        labelDirectionNorth->setStatusTip(QApplication::translate("CrowdQtClass", "Show values for direction north.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        labelDirectionNorth->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">N</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDirectionEast->setToolTip(QApplication::translate("CrowdQtClass", "Show values for direction east.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        labelDirectionEast->setStatusTip(QApplication::translate("CrowdQtClass", "Show values for direction east.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        labelDirectionEast->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">E</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDirectionSouth->setToolTip(QApplication::translate("CrowdQtClass", "Show values for direction south.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        labelDirectionSouth->setStatusTip(QApplication::translate("CrowdQtClass", "Show values for direction south.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        labelDirectionSouth->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">S</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        labelDirectionWest->setToolTip(QApplication::translate("CrowdQtClass", "Show values for direction west.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        labelDirectionWest->setStatusTip(QApplication::translate("CrowdQtClass", "Show values for direction west.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        labelDirectionWest->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">W</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonAgentGroup0->setToolTip(QApplication::translate("CrowdQtClass", "Show field for agent group 0.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonAgentGroup0->setStatusTip(QApplication::translate("CrowdQtClass", "Show field for agent group 0.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonAgentGroup0->setText(QString());
#ifndef QT_NO_TOOLTIP
        radioButtonAgentGroup1->setToolTip(QApplication::translate("CrowdQtClass", "Show field for agent group 1.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonAgentGroup1->setStatusTip(QApplication::translate("CrowdQtClass", "Show field for agent group 1.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonAgentGroup1->setText(QString());
#ifndef QT_NO_TOOLTIP
        radioButtonAgentGroup2->setToolTip(QApplication::translate("CrowdQtClass", "Show field for agent group 2.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonAgentGroup2->setStatusTip(QApplication::translate("CrowdQtClass", "Show field for agent group 2.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonAgentGroup2->setText(QString());
#ifndef QT_NO_TOOLTIP
        radioButtonAgentGroup3->setToolTip(QApplication::translate("CrowdQtClass", "Show field for agent group 3.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonAgentGroup3->setStatusTip(QApplication::translate("CrowdQtClass", "Show field for agent group 3.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonAgentGroup3->setText(QString());
        labelGroups->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt;\">Agent Group</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        labelGroup0->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt; color:#aaaa00;\">0</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        labelGroup1->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt; color:#00aaaa;\">1</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        labelGroup2->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt; color:#aa00aa;\">2</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        labelGroup3->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:10pt; color:#aaaaaa;\">3</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("CrowdQtClass", "Fields", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonShowGradient->setToolTip(QApplication::translate("CrowdQtClass", "Show gradient direction\n"
"[7]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonShowGradient->setStatusTip(QApplication::translate("CrowdQtClass", "Show gradient direction [7]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonShowGradient->setText(QApplication::translate("CrowdQtClass", "Gradient direction", 0, QApplication::UnicodeUTF8));
        radioButtonShowGradient->setShortcut(QApplication::translate("CrowdQtClass", "7", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonShowAverageVelocity->setToolTip(QApplication::translate("CrowdQtClass", "Show average velocity direction\n"
"[3]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonShowAverageVelocity->setStatusTip(QApplication::translate("CrowdQtClass", "Show average velocity direction [3]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonShowAverageVelocity->setText(QApplication::translate("CrowdQtClass", "Average velocity direction", 0, QApplication::UnicodeUTF8));
        radioButtonShowAverageVelocity->setShortcut(QApplication::translate("CrowdQtClass", "3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonShowPotential->setToolTip(QApplication::translate("CrowdQtClass", "Show potential\n"
"[6]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonShowPotential->setStatusTip(QApplication::translate("CrowdQtClass", "Show potential [6]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonShowPotential->setText(QApplication::translate("CrowdQtClass", "Potential", 0, QApplication::UnicodeUTF8));
        radioButtonShowPotential->setShortcut(QApplication::translate("CrowdQtClass", "6", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonShowDensity->setToolTip(QApplication::translate("CrowdQtClass", "Show density\n"
"[2]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonShowDensity->setStatusTip(QApplication::translate("CrowdQtClass", "Show density [2]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonShowDensity->setText(QApplication::translate("CrowdQtClass", "Density", 0, QApplication::UnicodeUTF8));
        radioButtonShowDensity->setShortcut(QApplication::translate("CrowdQtClass", "2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonShowSpeed->setToolTip(QApplication::translate("CrowdQtClass", "Show speed\n"
"[4]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonShowSpeed->setStatusTip(QApplication::translate("CrowdQtClass", "Show speed [4]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonShowSpeed->setText(QApplication::translate("CrowdQtClass", "Speed", 0, QApplication::UnicodeUTF8));
        radioButtonShowSpeed->setShortcut(QApplication::translate("CrowdQtClass", "4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonShowCost->setToolTip(QApplication::translate("CrowdQtClass", "Show cost\n"
"[5]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonShowCost->setStatusTip(QApplication::translate("CrowdQtClass", "Show cost [5]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonShowCost->setText(QApplication::translate("CrowdQtClass", "Cost", 0, QApplication::UnicodeUTF8));
        radioButtonShowCost->setShortcut(QApplication::translate("CrowdQtClass", "5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonShowDiscomfort->setToolTip(QApplication::translate("CrowdQtClass", "Show discomfort\n"
"[1]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButtonShowDiscomfort->setStatusTip(QApplication::translate("CrowdQtClass", "Show discomfort [1]", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        radioButtonShowDiscomfort->setText(QApplication::translate("CrowdQtClass", "Discomfort", 0, QApplication::UnicodeUTF8));
        radioButtonShowDiscomfort->setShortcut(QApplication::translate("CrowdQtClass", "1", 0, QApplication::UnicodeUTF8));
        mapAlphaLabelValue->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">n/a</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        mapAlphaLabelName->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Opacity</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mapAlphaSlider->setToolTip(QApplication::translate("CrowdQtClass", "Opacity of the map texture.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mapAlphaSlider->setStatusTip(QApplication::translate("CrowdQtClass", "Opacity of the map texture.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        gradientArrowsAlphaLabelValue->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">n/a</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        gradientArrowsAlphaSlider->setToolTip(QApplication::translate("CrowdQtClass", "Opacity of gradient arrows.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        gradientArrowsAlphaSlider->setStatusTip(QApplication::translate("CrowdQtClass", "Opacity of gradient arrows.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        gradientArrowsAlphaLabelName->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Arrow opacity</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("CrowdQtClass", "Map", 0, QApplication::UnicodeUTF8));
        label20->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">anisotropic</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        label20_2->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">per group</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        gradientInterpolateLabelName->setText(QApplication::translate("CrowdQtClass", "Filter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        gradientInterpolateYes->setToolTip(QApplication::translate("CrowdQtClass", "Show gradient per cell.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        gradientInterpolateYes->setStatusTip(QApplication::translate("CrowdQtClass", "Show gradient per cell.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        gradientInterpolateYes->setText(QApplication::translate("CrowdQtClass", "Linear", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        gradientInterpolateNo->setToolTip(QApplication::translate("CrowdQtClass", "Show gradient bilinearly filtered,\n"
"as used during agent movement computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        gradientInterpolateNo->setStatusTip(QApplication::translate("CrowdQtClass", "Show gradient bilinearly filtered, as used during agent movement computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        gradientInterpolateNo->setText(QApplication::translate("CrowdQtClass", "Nearest", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("CrowdQtClass", "Agents", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBoxIsDrawingSplatAreas->setToolTip(QApplication::translate("CrowdQtClass", "Render agent splat areas.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkBoxIsDrawingSplatAreas->setStatusTip(QApplication::translate("CrowdQtClass", "Render agent splat areas.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        checkBoxIsDrawingSplatAreas->setText(QApplication::translate("CrowdQtClass", "Splat areas", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        isDrawingSprites->setToolTip(QApplication::translate("CrowdQtClass", "Render agent sprites.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        isDrawingSprites->setStatusTip(QApplication::translate("CrowdQtClass", "Render agent sprites.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        isDrawingSprites->setText(QApplication::translate("CrowdQtClass", "Sprites", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("CrowdQtClass", "Tiles", 0, QApplication::UnicodeUTF8));
        workGroupsAlphaLabelValue->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">n/a</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        workItemsAlphaLabelValue->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">n/a</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        workItemsAlphaSlider->setToolTip(QApplication::translate("CrowdQtClass", "Opacity of work-item overlay.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        workItemsAlphaSlider->setStatusTip(QApplication::translate("CrowdQtClass", "Opacity of work-item overlay.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        workItemsAlphaLabelName->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Opacity</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        workGroupsAlphaSlider->setToolTip(QApplication::translate("CrowdQtClass", "Opacity of work-group overlay.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        workGroupsAlphaSlider->setStatusTip(QApplication::translate("CrowdQtClass", "Opacity of work-group overlay.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        workGroupsAlphaLabelName->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Opacity</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupStatesAlphaSlider->setToolTip(QApplication::translate("CrowdQtClass", "Opacity of selective update tile states overlay.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        groupStatesAlphaSlider->setStatusTip(QApplication::translate("CrowdQtClass", "Opacity of selective update tile states overlay.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        groupStatesAlphaLabelValue->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">n/a</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        groupStatesAlphaLabelName->setText(QApplication::translate("CrowdQtClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Opacity</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("CrowdQtClass", "Work-groups", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("CrowdQtClass", "Work-items", 0, QApplication::UnicodeUTF8));
        labelSelectiveUpdateState->setText(QApplication::translate("CrowdQtClass", "Selective update\n"
"tile states", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CrowdQtClass", "Solver", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        iterationsLabelValue->setToolTip(QApplication::translate("CrowdQtClass", "Outer iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        iterationsLabelValue->setStatusTip(QApplication::translate("CrowdQtClass", "Outer iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        iterationsLabelValue->setText(QApplication::translate("CrowdQtClass", "n/a", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        iterationsLabelName->setToolTip(QApplication::translate("CrowdQtClass", "Outer iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        iterationsLabelName->setStatusTip(QApplication::translate("CrowdQtClass", "Outer iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        iterationsLabelName->setText(QApplication::translate("CrowdQtClass", "Outer steps", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        iterationsSlider->setToolTip(QApplication::translate("CrowdQtClass", "Outer iteration steps for potential computation..", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        iterationsSlider->setStatusTip(QApplication::translate("CrowdQtClass", "Outer iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QApplication::translate("CrowdQtClass", "Inner iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label_7->setStatusTip(QApplication::translate("CrowdQtClass", "Inner iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_7->setText(QApplication::translate("CrowdQtClass", "Inner steps", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        innerLoopCountLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Inner iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        innerLoopCountLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Inner iteration steps for potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        label_8->setToolTip(QApplication::translate("CrowdQtClass", "Total number of iterations used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label_8->setStatusTip(QApplication::translate("CrowdQtClass", "Total number of iterations used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_8->setText(QApplication::translate("CrowdQtClass", "Outer * Inner * Unroll Factor =", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        workItemIterations->setToolTip(QApplication::translate("CrowdQtClass", "Total number of iterations used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        workItemIterations->setStatusTip(QApplication::translate("CrowdQtClass", "Total number of iterations used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        workItemIterations->setText(QApplication::translate("CrowdQtClass", "20", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        isBreakingAfterSolverStep->setToolTip(QApplication::translate("CrowdQtClass", "Stop after each step for visualization.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        isBreakingAfterSolverStep->setStatusTip(QApplication::translate("CrowdQtClass", "Stop after each step for visualization.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        isBreakingAfterSolverStep->setText(QApplication::translate("CrowdQtClass", "Break after each solver step", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_21->setToolTip(QApplication::translate("CrowdQtClass", "Inner loop unroll factor used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label_21->setStatusTip(QApplication::translate("CrowdQtClass", "Inner loop unroll factor used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_21->setText(QApplication::translate("CrowdQtClass", "Inner unroll factor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        innerUnrollFactor->setToolTip(QApplication::translate("CrowdQtClass", "Inner loop unroll factor used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        innerUnrollFactor->setStatusTip(QApplication::translate("CrowdQtClass", "Inner loop unroll factor used in potential computation.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        innerUnrollFactor->setText(QApplication::translate("CrowdQtClass", "n/a", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("CrowdQtClass", "Tile Update Method", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        isUpdatingAll->setToolTip(QApplication::translate("CrowdQtClass", "Update all tiles per iteration.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        isUpdatingAll->setStatusTip(QApplication::translate("CrowdQtClass", "Update all tiles per iteration.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        isUpdatingAll->setText(QApplication::translate("CrowdQtClass", "Update all", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        isUpdatingSelectively->setToolTip(QApplication::translate("CrowdQtClass", "Selectively update tiles per iteration.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        isUpdatingSelectively->setStatusTip(QApplication::translate("CrowdQtClass", "Selectively update tiles per iteration.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        isUpdatingSelectively->setText(QApplication::translate("CrowdQtClass", "Update selectively", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("CrowdQtClass", "Path Weights", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CrowdQtClass", "Length", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CrowdQtClass", "Time spent", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CrowdQtClass", "Discomfort felt", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lengthLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Cost weight factor for path length.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lengthLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Cost weight factor for path length.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        timeLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Cost weight factor for time spent on path.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        timeLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Cost weight factor for time spent on path.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        discomfortLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Cost weight factor for discomfort on path.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        discomfortLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Cost weight factor for discomfort on path.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        groupBox_7->setTitle(QApplication::translate("CrowdQtClass", "Density", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CrowdQtClass", "Minimum", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CrowdQtClass", "Maximum", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        minimumDensityLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Minimum agent density for speed computation (\342\211\2450.5).", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        minimumDensityLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Minimum agent density for speed computation (\342\211\2450.5).", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        maximumDensityLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Maximum agent density for speed computation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        maximumDensityLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Maximum agent density for speed computation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        groupBox_12->setTitle(QApplication::translate("CrowdQtClass", "Discomfort Brush", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        discomfortBrushRadiusLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Radius of the discomfort circle.\n"
" [Middle Mouse Button] to place.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        discomfortBrushRadiusLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Radius of the discomfort circle. [Middle Mouse Button] to place.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_18->setText(QApplication::translate("CrowdQtClass", "Radius", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        discomfortBrushIntensityLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Intensity factor for the discomfort circle.\n"
" [Middle Mouse Button] to place in view.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        discomfortBrushIntensityLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Intensity factor for the discomfort circle. [Middle Mouse Button] to place in view.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_20->setText(QApplication::translate("CrowdQtClass", "Intensity", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("CrowdQtClass", "Display", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("CrowdQtClass", "Computation", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CrowdQtClass", "Movement", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_6->setToolTip(QApplication::translate("CrowdQtClass", "Agent speed is clamped to this.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label_6->setStatusTip(QApplication::translate("CrowdQtClass", "Agent speed is clamped to this.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_6->setText(QApplication::translate("CrowdQtClass", "Maximum speed", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        maximumSpeedLineEdit->setToolTip(QApplication::translate("CrowdQtClass", "Agent speed is clamped to this.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        maximumSpeedLineEdit->setStatusTip(QApplication::translate("CrowdQtClass", "Agent speed is clamped to this.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        resolveCollisionsCheckBox->setToolTip(QApplication::translate("CrowdQtClass", "Resolve collisions between agents.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        resolveCollisionsCheckBox->setStatusTip(QApplication::translate("CrowdQtClass", "Resolve collisions between agents.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        resolveCollisionsCheckBox->setText(QApplication::translate("CrowdQtClass", "Resolve collisions", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exitPark->setToolTip(QApplication::translate("CrowdQtClass", "Park agents that reach their goal outside map.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        exitPark->setStatusTip(QApplication::translate("CrowdQtClass", "Park agents that reach their goal outside map.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        exitPark->setText(QApplication::translate("CrowdQtClass", "Park", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exitChangeGroup->setToolTip(QApplication::translate("CrowdQtClass", "Agent that reaches its goal changes to next agent group.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        exitChangeGroup->setStatusTip(QApplication::translate("CrowdQtClass", "Agent that reaches its goal changes to next agent group.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        exitChangeGroup->setText(QApplication::translate("CrowdQtClass", "Change Group", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exitRespawn->setToolTip(QApplication::translate("CrowdQtClass", "Parked agents respawn at entry area.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        exitRespawn->setStatusTip(QApplication::translate("CrowdQtClass", "Parked agents respawn at entry area.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        exitRespawn->setText(QApplication::translate("CrowdQtClass", "Respawn", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("CrowdQtClass", "toolBar", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CrowdQtClass", "Log", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBoxPrintProfiling->setToolTip(QApplication::translate("CrowdQtClass", "Print profiling info to text window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkBoxPrintProfiling->setStatusTip(QApplication::translate("CrowdQtClass", "Print profiling info to text window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        checkBoxPrintProfiling->setText(QApplication::translate("CrowdQtClass", "Update profiling info", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBoxProfileDetails->setToolTip(QApplication::translate("CrowdQtClass", "Provide additional information and profile OpenCL kernels.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        checkBoxProfileDetails->setStatusTip(QApplication::translate("CrowdQtClass", "Provide additional information and profile OpenCL kernels.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        checkBoxProfileDetails->setText(QApplication::translate("CrowdQtClass", "Detailed profiling (slow)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("CrowdQtClass", "Profiler", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("CrowdQtClass", "Memory", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("CrowdQtClass", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("CrowdQtClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CrowdQtClass: public Ui_CrowdQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CROWDQT_H
