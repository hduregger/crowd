#include "Settings.h"

#include <QSettings>

#include "Exception.h"
#include "MainWindow.h"


const float   Settings::MINIMAL_RADIUS                 = 0.4f;

const QString Settings::DEFAULT_CONFIG_FILE            = "default.cfg";

const QString Settings::MAP_MAP_FILE                   = "Map/mapFile";
const QString Settings::MAP_DISCOMFORT_FILE            = "Map/discomfortFile";
const QString Settings::MAP_EXIT_FILE                  = "Map/exitFile";


const QString Settings::SOLVER_WORK_GROUP_SIDE_LENGTH  = "Solver/workGroupSideLength";
const QString Settings::SOLVER_IS_USING_GPU            = "Solver/isUsingGPU";
const QString Settings::SOLVER_OUTER_ITERATIONS        = "Solver/outerIterations";

const QString Settings::SOLVER_COST_WEIGHT_LENGTH      = "Solver/costWeightLength";
const QString Settings::SOLVER_COST_WEIGHT_TIME        = "Solver/costWeightTime";
const QString Settings::SOLVER_COST_WEIGHT_DISCOMFORT  = "Solver/costWeightDiscomfort";

const QString Settings::AGENT_COUNT                    = "Agents/count";
const QString Settings::AGENT_MINIMUM_RADIUS           = "Agents/minimumRadius";
const QString Settings::AGENT_MAXIMUM_RADIUS           = "Agents/maximumRadius";
const QString Settings::AGENT_SEED                     = "Agents/seed";

const QString Settings::AGENT_GROUP0_TEXTURE           = "Agents/group0Texture";
const QString Settings::AGENT_GROUP1_TEXTURE           = "Agents/group1Texture";
const QString Settings::AGENT_GROUP2_TEXTURE           = "Agents/group2Texture";
const QString Settings::AGENT_GROUP3_TEXTURE           = "Agents/group3Texture";

const QString Settings::AGENT_ENTRY0_LOWER_LEFT_X      = "Agents.Entry1/lowerLeftX";
const QString Settings::AGENT_ENTRY0_LOWER_LEFT_Y      = "Agents.Entry1/lowerLeftY";
const QString Settings::AGENT_ENTRY0_UPPER_RIGHT_X     = "Agents.Entry1/upperRightX";
const QString Settings::AGENT_ENTRY0_UPPER_RIGHT_Y     = "Agents.Entry1/upperRightY";

const QString Settings::AGENT_ENTRY1_LOWER_LEFT_X      = "Agents.Entry2/lowerLeftX";
const QString Settings::AGENT_ENTRY1_LOWER_LEFT_Y      = "Agents.Entry2/lowerLeftY";
const QString Settings::AGENT_ENTRY1_UPPER_RIGHT_X     = "Agents.Entry2/upperRightX";
const QString Settings::AGENT_ENTRY1_UPPER_RIGHT_Y     = "Agents.Entry2/upperRightY";

const QString Settings::AGENT_ENTRY2_LOWER_LEFT_X      = "Agents.Entry3/lowerLeftX";
const QString Settings::AGENT_ENTRY2_LOWER_LEFT_Y      = "Agents.Entry3/lowerLeftY";
const QString Settings::AGENT_ENTRY2_UPPER_RIGHT_X     = "Agents.Entry3/upperRightX";
const QString Settings::AGENT_ENTRY2_UPPER_RIGHT_Y     = "Agents.Entry3/upperRightY";

const QString Settings::AGENT_ENTRY3_LOWER_LEFT_X      = "Agents.Entry4/lowerLeftX";
const QString Settings::AGENT_ENTRY3_LOWER_LEFT_Y      = "Agents.Entry4/lowerLeftY";
const QString Settings::AGENT_ENTRY3_UPPER_RIGHT_X     = "Agents.Entry4/upperRightX";
const QString Settings::AGENT_ENTRY3_UPPER_RIGHT_Y     = "Agents.Entry4/upperRightY";

const QString Settings::AGENT_META_MOVEMENT_MODE       = "Agents/movementMode";

const QString Settings::DEBUG_IS_PROFILING_QUEUE       = "Debug/isProfilingQueue";


Settings::Settings(QString filename)
:   mapFile(""),
    discomfortFile(""),
    exitFile(""),
    workGroupSideLength(0),
    isUsingGPU(true),
    isProfilingQueue(false),
    agentCount(0),
    agentSeed(0),
    agentEntry0(Vector4i(0, 0, 0, 0)),
    agentEntry1(Vector4i(0, 0, 0, 0)),
    agentEntry2(Vector4i(0, 0, 0, 0)),
    agentEntry3(Vector4i(0, 0, 0, 0)),
    agentsGroup0Texture(""),
    agentsGroup1Texture(""),
    agentsGroup2Texture(""),
    agentsGroup3Texture(""),
    minimumRadius(0.0f),
    maximumRadius(0.0f),
    outerIterations(1),
    costWeightLength(1.0f),
    costWeightTime(1.0f),
    costWeightDiscomfort(1.0f),
    movementMode(0)
{
    QSettings* settings = new QSettings(filename, QSettings::IniFormat);

    checkExist(settings, Settings::MAP_MAP_FILE);
    mapFile        = settings->value(Settings::MAP_MAP_FILE).toString();

    checkExist(settings, Settings::MAP_DISCOMFORT_FILE);
    discomfortFile = settings->value(Settings::MAP_DISCOMFORT_FILE).toString();

    checkExist(settings, Settings::MAP_EXIT_FILE);
    exitFile = settings->value(Settings::MAP_EXIT_FILE).toString();


    bool isValid = true;

    checkExist(settings, Settings::AGENT_COUNT);
    agentCount = settings->value(Settings::AGENT_COUNT).toUInt(&isValid);
    checkValid(isValid, "Invalid agent count!");

    checkExist(settings, Settings::AGENT_SEED);
    agentSeed = settings->value(Settings::AGENT_SEED).toInt(&isValid);
    checkValid(isValid, "Invalid agent seed!");

    checkExist(settings, Settings::AGENT_META_MOVEMENT_MODE);
    movementMode = settings->value(Settings::AGENT_META_MOVEMENT_MODE).toInt(&isValid);
    checkValid(isValid, "Invalid agent movement mode!");

    checkExist(settings, Settings::SOLVER_WORK_GROUP_SIDE_LENGTH);
    workGroupSideLength = static_cast<size_t> (settings->value(Settings::SOLVER_WORK_GROUP_SIDE_LENGTH).toUInt(&isValid));
    checkValid(isValid, "Invalid work group side length!");

    checkExist(settings, Settings::SOLVER_OUTER_ITERATIONS);
    outerIterations = static_cast<size_t> (settings->value(Settings::SOLVER_OUTER_ITERATIONS).toInt(&isValid));
    checkValid(isValid, "Invalid number of outer iterations!");

    checkExist(settings, Settings::SOLVER_IS_USING_GPU);
    isUsingGPU = settings->value(Settings::SOLVER_IS_USING_GPU).toBool();


    checkExist(settings, Settings::SOLVER_COST_WEIGHT_LENGTH);
    costWeightLength = settings->value(Settings::SOLVER_COST_WEIGHT_LENGTH).toFloat(&isValid);
    checkValid(isValid, "Invalid cost weight for length!");

    checkExist(settings, Settings::SOLVER_COST_WEIGHT_TIME);
    costWeightTime = settings->value(Settings::SOLVER_COST_WEIGHT_TIME).toFloat(&isValid);
    checkValid(isValid, "Invalid cost weight for time!");

    checkExist(settings, Settings::SOLVER_COST_WEIGHT_DISCOMFORT);
    costWeightDiscomfort = settings->value(Settings::SOLVER_COST_WEIGHT_DISCOMFORT).toFloat(&isValid);
    checkValid(isValid, "Invalid cost weight for discomfort!");


    checkExist(settings, Settings::AGENT_ENTRY0_LOWER_LEFT_X);
    agentEntry0.x = settings->value(Settings::AGENT_ENTRY0_LOWER_LEFT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 1!");

    checkExist(settings, Settings::AGENT_ENTRY0_LOWER_LEFT_Y);
    agentEntry0.y = settings->value(Settings::AGENT_ENTRY0_LOWER_LEFT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 1!");

    checkExist(settings, Settings::AGENT_ENTRY0_UPPER_RIGHT_X);
    agentEntry0.z = settings->value(Settings::AGENT_ENTRY0_UPPER_RIGHT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 1!");

    checkExist(settings, Settings::AGENT_ENTRY0_UPPER_RIGHT_Y);
    agentEntry0.w = settings->value(Settings::AGENT_ENTRY0_UPPER_RIGHT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 1!");


    checkExist(settings, Settings::AGENT_ENTRY1_LOWER_LEFT_X);
    agentEntry1.x = settings->value(Settings::AGENT_ENTRY1_LOWER_LEFT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 2!");

    checkExist(settings, Settings::AGENT_ENTRY1_LOWER_LEFT_Y);
    agentEntry1.y = settings->value(Settings::AGENT_ENTRY1_LOWER_LEFT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 2!");

    checkExist(settings, Settings::AGENT_ENTRY1_UPPER_RIGHT_X);
    agentEntry1.z = settings->value(Settings::AGENT_ENTRY1_UPPER_RIGHT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 2!");

    checkExist(settings, Settings::AGENT_ENTRY1_UPPER_RIGHT_Y);
    agentEntry1.w = settings->value(Settings::AGENT_ENTRY1_UPPER_RIGHT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 2!");


    checkExist(settings, Settings::AGENT_ENTRY2_LOWER_LEFT_X);
    agentEntry2.x = settings->value(Settings::AGENT_ENTRY2_LOWER_LEFT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 3!");

    checkExist(settings, Settings::AGENT_ENTRY2_LOWER_LEFT_Y);
    agentEntry2.y = settings->value(Settings::AGENT_ENTRY2_LOWER_LEFT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 3!");

    checkExist(settings, Settings::AGENT_ENTRY2_UPPER_RIGHT_X);
    agentEntry2.z = settings->value(Settings::AGENT_ENTRY2_UPPER_RIGHT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 3!");

    checkExist(settings, Settings::AGENT_ENTRY2_UPPER_RIGHT_Y);
    agentEntry2.w = settings->value(Settings::AGENT_ENTRY2_UPPER_RIGHT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 3!");


    checkExist(settings, Settings::AGENT_ENTRY3_LOWER_LEFT_X);
    agentEntry3.x = settings->value(Settings::AGENT_ENTRY3_LOWER_LEFT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 4!");

    checkExist(settings, Settings::AGENT_ENTRY3_LOWER_LEFT_Y);
    agentEntry3.y = settings->value(Settings::AGENT_ENTRY3_LOWER_LEFT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 4!");

    checkExist(settings, Settings::AGENT_ENTRY3_UPPER_RIGHT_X);
    agentEntry3.z = settings->value(Settings::AGENT_ENTRY3_UPPER_RIGHT_X).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 4!");

    checkExist(settings, Settings::AGENT_ENTRY3_UPPER_RIGHT_Y);
    agentEntry3.w = settings->value(Settings::AGENT_ENTRY3_UPPER_RIGHT_Y).toInt(&isValid);
    checkValid(isValid, "Invalid agent entry 4!");

    checkExist(settings, Settings::AGENT_GROUP0_TEXTURE);
    agentsGroup0Texture = settings->value(Settings::AGENT_GROUP0_TEXTURE).toString();
    checkExist(settings, Settings::AGENT_GROUP1_TEXTURE);
    agentsGroup1Texture = settings->value(Settings::AGENT_GROUP1_TEXTURE).toString();
    checkExist(settings, Settings::AGENT_GROUP2_TEXTURE);
    agentsGroup2Texture = settings->value(Settings::AGENT_GROUP2_TEXTURE).toString();
    checkExist(settings, Settings::AGENT_GROUP3_TEXTURE);
    agentsGroup3Texture = settings->value(Settings::AGENT_GROUP3_TEXTURE).toString();


    checkExist(settings, Settings::DEBUG_IS_PROFILING_QUEUE);
    isProfilingQueue = settings->value(Settings::DEBUG_IS_PROFILING_QUEUE).toBool();

    checkExist(settings, Settings::AGENT_MINIMUM_RADIUS);
    minimumRadius = settings->value(Settings::AGENT_MINIMUM_RADIUS).toFloat(&isValid);
    checkValid(isValid, "Invalid minimum agent radius!");

    checkExist(settings, Settings::AGENT_MAXIMUM_RADIUS);
    maximumRadius = settings->value(Settings::AGENT_MAXIMUM_RADIUS).toFloat(&isValid);
    checkValid(isValid, "Invalid maximum agent radius!");

    if (minimumRadius < Settings::MINIMAL_RADIUS)
    {
        throw Exception("Minimum radius is less than " + QString::number(Settings::MINIMAL_RADIUS) + ". Check your config file!");
    }

    if (maximumRadius < minimumRadius)
    {
        throw Exception("Maximum radius is less than minimum radius. Check your config file!");
    }

    if ((outerIterations < 1) || (outerIterations > 200))
    {
        throw Exception("Outer iteration count must be inside [1, 200]. Check your config file!");
    }


    if ((costWeightLength < MainWindow::WEIGHT_LOWER_BOUND) || (costWeightLength > MainWindow::WEIGHT_UPPER_BOUND))
    {
        throw Exception("Cost weight length must be inside [1, 200]. Check your config file!");
    }

    if ((costWeightTime < MainWindow::WEIGHT_LOWER_BOUND) || (costWeightTime > MainWindow::WEIGHT_UPPER_BOUND))
    {
        throw Exception("Cost weight time must be inside [1, 200]. Check your config file!");
    }

    if ((costWeightDiscomfort < MainWindow::WEIGHT_LOWER_BOUND) || (costWeightDiscomfort > MainWindow::WEIGHT_UPPER_BOUND))
    {
        throw Exception("Cost weight discomfort must be inside [1, 200]. Check your config file!");
    }

    if ((movementMode != 0) && (movementMode != 1) && (movementMode != 2))
    {
        throw Exception("Agent movement mode must be 0 (Park), 1 (Change Group), or 2 (Respawn). Check your config file!");
    }

    delete settings;
}


Settings::~Settings()
{
}


void Settings::checkValid(bool isValid, QString errorMessage)
{
    if (!isValid)
    {
        throw Exception(errorMessage);
    }
}


void Settings::checkExist(const QSettings* settings, QString keyName)
{
    if (!settings->contains(keyName))
    {
        throw Exception("Settings do not contain an entry for \"" + keyName + "\"");
    }
}


void Settings::createDefault()
{
    QSettings* settings = new QSettings(Settings::DEFAULT_CONFIG_FILE, QSettings::IniFormat);

    settings->setValue(Settings::MAP_MAP_FILE, "");
    settings->setValue(Settings::MAP_DISCOMFORT_FILE, "");
    settings->setValue(Settings::MAP_EXIT_FILE, "");

    settings->setValue(Settings::AGENT_COUNT, 64);
    settings->setValue(Settings::AGENT_MINIMUM_RADIUS, 0.5);
    settings->setValue(Settings::AGENT_MAXIMUM_RADIUS, 1.0);
    settings->setValue(Settings::AGENT_SEED, -1);
    settings->setValue(Settings::AGENT_META_MOVEMENT_MODE, 0);

    settings->setValue(Settings::AGENT_GROUP0_TEXTURE, "");
    settings->setValue(Settings::AGENT_GROUP1_TEXTURE, "");
    settings->setValue(Settings::AGENT_GROUP2_TEXTURE, "");
    settings->setValue(Settings::AGENT_GROUP3_TEXTURE, "");

    settings->setValue(Settings::AGENT_ENTRY0_LOWER_LEFT_X,  100);
    settings->setValue(Settings::AGENT_ENTRY0_LOWER_LEFT_Y,  100);
    settings->setValue(Settings::AGENT_ENTRY0_UPPER_RIGHT_X, 110);
    settings->setValue(Settings::AGENT_ENTRY0_UPPER_RIGHT_Y, 110);

    settings->setValue(Settings::AGENT_ENTRY1_LOWER_LEFT_X,  100);
    settings->setValue(Settings::AGENT_ENTRY1_LOWER_LEFT_Y,  100);
    settings->setValue(Settings::AGENT_ENTRY1_UPPER_RIGHT_X, 110);
    settings->setValue(Settings::AGENT_ENTRY1_UPPER_RIGHT_Y, 110);

    settings->setValue(Settings::AGENT_ENTRY2_LOWER_LEFT_X,  100);
    settings->setValue(Settings::AGENT_ENTRY2_LOWER_LEFT_Y,  100);
    settings->setValue(Settings::AGENT_ENTRY2_UPPER_RIGHT_X, 110);
    settings->setValue(Settings::AGENT_ENTRY2_UPPER_RIGHT_Y, 110);

    settings->setValue(Settings::AGENT_ENTRY3_LOWER_LEFT_X,  100);
    settings->setValue(Settings::AGENT_ENTRY3_LOWER_LEFT_Y,  100);
    settings->setValue(Settings::AGENT_ENTRY3_UPPER_RIGHT_X, 110);
    settings->setValue(Settings::AGENT_ENTRY3_UPPER_RIGHT_Y, 110);

    settings->setValue(Settings::SOLVER_WORK_GROUP_SIDE_LENGTH, 16);
    settings->setValue(Settings::SOLVER_IS_USING_GPU, true);
    settings->setValue(Settings::SOLVER_OUTER_ITERATIONS, 75);

    settings->setValue(Settings::SOLVER_COST_WEIGHT_LENGTH, 1.0);
    settings->setValue(Settings::SOLVER_COST_WEIGHT_TIME, 1.0);
    settings->setValue(Settings::SOLVER_COST_WEIGHT_DISCOMFORT, 1.0);

    settings->setValue(Settings::DEBUG_IS_PROFILING_QUEUE, true);

    delete settings;
}

