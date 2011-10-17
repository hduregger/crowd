#ifndef LOGGER_H_
#define LOGGER_H_

#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include <QSplashScreen>
#include <QApplication>

#include "SplashScreen.h"


class Logger
{
public:

    static const char*      LOG_CONSOLE_TAG_CROWD;
    static const char*      LOG_CONSOLE_TAG_QT;

    static const char*      LOG_PRIORITY_TAG_DEBUG;
    static const char*      LOG_PRIORITY_TAG_INFO;
    static const char*      LOG_PRIORITY_TAG_WARNING;
    static const char*      LOG_PRIORITY_TAG_ERROR;
    static const char*      LOG_PRIORITY_TAG_CRITICAL;
    static const char*      LOG_PRIORITY_TAG_FATAL;



    static const QString    LOG_FILE;

                Logger(QString filename);
    virtual     ~Logger();

    void        clear();

    void        logInfo(QString text, bool isLoggingToFile = true, bool isLoggingToLogWindow = true) const;
    void        logWarning(QString text) const;
    void        logError(QString text) const;

    void        setLogWindow(QTextEdit* logWindow);
    void		setSplash(SplashScreen* splash, QApplication* application);


private:

    QTextEdit*      logWindow;
    QTextStream*    stream;
    QFile*          file;

    SplashScreen* 	splash;
    QApplication*   application;

    void        writeToFile(const QString text) const;
};

#endif /* LOGGER_H_ */
