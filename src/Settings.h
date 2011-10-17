#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QMetaType>
#include <QtGui/QApplication>
#include <QSettings>

#include "Vector4.h"
#include <CL/cl.h>


struct Settings
{
    static const float   MINIMAL_RADIUS;

    static const QString DEFAULT_CONFIG_FILE;

    static const QString MAP_MAP_FILE;
    static const QString MAP_DISCOMFORT_FILE;
    static const QString MAP_EXIT_FILE;

    static const QString SOLVER_WORK_GROUP_SIDE_LENGTH;
    static const QString SOLVER_IS_USING_GPU;
    static const QString SOLVER_OUTER_ITERATIONS;

    static const QString SOLVER_COST_WEIGHT_LENGTH;
    static const QString SOLVER_COST_WEIGHT_TIME;
    static const QString SOLVER_COST_WEIGHT_DISCOMFORT;

    static const QString AGENT_COUNT;
    static const QString AGENT_MINIMUM_RADIUS;
    static const QString AGENT_MAXIMUM_RADIUS;
    static const QString AGENT_SEED;

    static const QString AGENT_GROUP0_TEXTURE;
    static const QString AGENT_GROUP1_TEXTURE;
    static const QString AGENT_GROUP2_TEXTURE;
    static const QString AGENT_GROUP3_TEXTURE;

    static const QString AGENT_ENTRY0_LOWER_LEFT_X;
    static const QString AGENT_ENTRY0_LOWER_LEFT_Y;
    static const QString AGENT_ENTRY0_UPPER_RIGHT_X;
    static const QString AGENT_ENTRY0_UPPER_RIGHT_Y;

    static const QString AGENT_ENTRY1_LOWER_LEFT_X;
    static const QString AGENT_ENTRY1_LOWER_LEFT_Y;
    static const QString AGENT_ENTRY1_UPPER_RIGHT_X;
    static const QString AGENT_ENTRY1_UPPER_RIGHT_Y;

    static const QString AGENT_ENTRY2_LOWER_LEFT_X;
    static const QString AGENT_ENTRY2_LOWER_LEFT_Y;
    static const QString AGENT_ENTRY2_UPPER_RIGHT_X;
    static const QString AGENT_ENTRY2_UPPER_RIGHT_Y;

    static const QString AGENT_ENTRY3_LOWER_LEFT_X;
    static const QString AGENT_ENTRY3_LOWER_LEFT_Y;
    static const QString AGENT_ENTRY3_UPPER_RIGHT_X;
    static const QString AGENT_ENTRY3_UPPER_RIGHT_Y;

    static const QString AGENT_META_MOVEMENT_MODE;

    static const QString DEBUG_IS_PROFILING_QUEUE;


    QString     mapFile;
    QString     discomfortFile;
    QString     exitFile;


    size_t      workGroupSideLength;
    bool        isUsingGPU;
    bool        isProfilingQueue;

    uint        agentCount;

    int         agentSeed;

    Vector4i    agentEntry0;
    Vector4i    agentEntry1;
    Vector4i    agentEntry2;
    Vector4i    agentEntry3;

    QString     agentsGroup0Texture;
    QString     agentsGroup1Texture;
    QString     agentsGroup2Texture;
    QString     agentsGroup3Texture;

    cl_float    minimumRadius;
    cl_float    maximumRadius;

    int         outerIterations;

    cl_float    costWeightLength;
    cl_float    costWeightTime;
    cl_float    costWeightDiscomfort;

    int         movementMode;

                Settings(QString filename);
    virtual     ~Settings();

    static void createDefault();

private:

    void        checkExist(const QSettings* settings, QString keyName);
    void        checkValid(bool isValid, QString errorMessage);
};

#endif /* SETTINGS_H_ */
