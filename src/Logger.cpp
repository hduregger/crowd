#include "Logger.h"
#include "Exception.h"

#include <iostream>

const QString Logger::LOG_FILE                    = "crowd.log";

const char*   Logger::LOG_CONSOLE_TAG_CROWD       = "[Crowd] ";
const char*   Logger::LOG_CONSOLE_TAG_QT          = "[Qt   ] ";


const char*   Logger::LOG_PRIORITY_TAG_DEBUG        = "Debug    - ";
const char*   Logger::LOG_PRIORITY_TAG_INFO         = "Info     - ";
const char*   Logger::LOG_PRIORITY_TAG_WARNING      = "Warning  - ";
const char*   Logger::LOG_PRIORITY_TAG_ERROR        = "Error    - ";
const char*   Logger::LOG_PRIORITY_TAG_CRITICAL     = "Critical - ";
const char*   Logger::LOG_PRIORITY_TAG_FATAL        = "Fatal    - ";


Logger::Logger(QString filename)
:   logWindow(NULL),
    splash(NULL),
    application(NULL)
{
    file = new QFile(filename);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << LOG_CONSOLE_TAG_CROWD << "Could not open file \"" << filename.toAscii().data() << "\" for use as log file" << std::endl;

        throw Exception();
    }

    stream = new QTextStream(file);
}

Logger::~Logger()
{
    delete stream;
    delete file;
}


void Logger::clear()
{
    if (logWindow != NULL)
    {
        logWindow->clear();
    }
}


void Logger::writeToFile(const QString text) const
{
    stream->operator<<( text);
    stream->flush();
}


void Logger::logInfo(QString text, bool isLoggingToFile, bool isLoggingToLogWindow) const
{
    if ((splash != NULL) && (application != NULL))
    {
        splash->showStatusMessage(text, Qt::black);
        application->processEvents();
    }

    text = LOG_PRIORITY_TAG_INFO + text;

    if ((logWindow != NULL) && isLoggingToLogWindow)
    {
        logWindow->setTextColor(Qt::black);
        logWindow->append(text);
    }

    if (isLoggingToFile)
    {
        writeToFile(text + "\n");
    }

    std::cout << LOG_CONSOLE_TAG_CROWD << text.toAscii().data() << std::endl;
}


void Logger::logWarning(QString text) const
{
    if ((splash != NULL) && (application != NULL))
    {
        splash->showStatusMessage(text, Qt::black);
        application->processEvents();
    }

    text = LOG_PRIORITY_TAG_WARNING + text;

    if (logWindow != NULL)
    {
        logWindow->setTextColor(Qt::darkYellow);
        logWindow->append(text);
    }

    writeToFile(text + "\n");
    std::cout << LOG_CONSOLE_TAG_CROWD << text.toAscii().data() << std::endl;
}


void Logger::logError(QString text) const
{
    if ((splash != NULL) && (application != NULL))
    {
        splash->showStatusMessage(text, Qt::black);
        application->processEvents();
    }

    text = LOG_PRIORITY_TAG_ERROR + text;

    if (logWindow != NULL)
    {
        logWindow->setTextColor(Qt::darkRed);
        logWindow->append(text);
    }

    writeToFile(text + "\n");
    std::cerr << LOG_CONSOLE_TAG_CROWD << text.toAscii().data() << std::endl;
}


void Logger::setLogWindow(QTextEdit* logWindow)
{
    this->logWindow = logWindow;
}


void Logger::setSplash(SplashScreen* splash, QApplication* application)
{
	this->splash      = splash;
	this->application = application;
}
