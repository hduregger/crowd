#include <QMetaType>
#include <QtGui/QApplication>

#include <iostream>

#include "Application.h"
#include "MainWindow.h"
#include "Exception.h"
#include "Settings.h"



void messageHandler(QtMsgType type, const char* message)
{
    std::cout << Logger::LOG_CONSOLE_TAG_QT;

    switch (type)
    {
        case QtDebugMsg:
        {
            std::cout << Logger::LOG_PRIORITY_TAG_DEBUG;
            break;
        }
        case QtWarningMsg:
        {
            std::cout << Logger::LOG_PRIORITY_TAG_WARNING;
            break;
        }

        case QtCriticalMsg:
        {
            std::cout << Logger::LOG_PRIORITY_TAG_CRITICAL;
            break;
        }

        case QtFatalMsg:
        {
            std::cout << Logger::LOG_PRIORITY_TAG_FATAL;
            break;
        }
    }

    std::cout << message << std::endl;
}


int main(int argc, char *argv[])
{
    int ret = 0;

    qInstallMsgHandler(messageHandler);

    std::cout << "Running as \"";

    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }

    std::cout << "\"" << std::endl;

    std::cout << "NOTE: Crowd and Qt console messages are tagged with \"" <<
            Logger::LOG_CONSOLE_TAG_CROWD << "\" and \"" << Logger::LOG_CONSOLE_TAG_QT << "\"." << std::endl;

    // Create logger that logs to file and console

    Logger logger(Logger::LOG_FILE);


    try
    {
        Application application(argc, argv, &logger);

        logger.logInfo(application.getName() + " - compiled on " + QString(__DATE__) + " at " + QString(__TIME__));

        QGL::setPreferredPaintEngine(QPaintEngine::OpenGL2);


        MainWindow mainWindow(&logger, application.getName());

        // Now that we have a window allow logger to log to log window too

        logger.setLogWindow(mainWindow.getLogWindow());

        logger.logInfo("Check the console output for further information.");
        logger.logInfo("The log area only lists crowd simulation related messages.");

        //
        // Retrieve config file settings
        //

        // If no config is specified

        if (argc < 2)
        {
            // Generate default file as base for editing

            Settings::createDefault();

            throw Exception("No configuration file specified. Please specify a configuration file to use. Generated default.cfg. Please check the content if you intend to use it.");
        }

        // Use given filename

        QString filename = argv[1];

        QFile settingsFile(filename);

        if (!settingsFile.exists())
        {
            throw Exception("No \"" + filename + "\" exists. If you need a default configuration, run the program without arguments.");
        }

        // Show configuration file name in window title

        QString canonicalFilePath = QFileInfo(settingsFile).canonicalFilePath();

        mainWindow.setWindowTitle(application.getName() + " - " + canonicalFilePath);

        // Read Qt settings from the file

        Settings settings(filename);

        logger.logInfo("Loaded settings from \"" + canonicalFilePath + "\"");

        // Initialize main window with logger fully set up

        mainWindow.initialize(&settings, &application);

        // Start Qt event loop

        ret = application.exec();
    }
    catch (Exception& e)
    {
        logger.setLogWindow(NULL);
        logger.setSplash(NULL, NULL);
        logger.logError(e.message);

        QApplication::exit(1);

        return 1;
    }
    catch (std::exception& e)
    {
        logger.setLogWindow(NULL);
        logger.setSplash(NULL, NULL);
        logger.logError("std::exception caught: " + QString(e.what()));

        QApplication::exit(1);

        return 1;
    }
    catch (...)
    {
        logger.setLogWindow(NULL);
        logger.setSplash(NULL, NULL);
        logger.logError("Unknown exception caught.");

        QApplication::exit(1);

        return 1;
    }


    // Note: workaround to prevent X and glibc error message flood on exit
    //       the flood comes from the X handlers of Qt maybe (-> QApplication)
    exit(ret);

    return ret;
}
