#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <QApplication>

#include "Logger.h"

class Application : public QApplication
{
public:

    static const    QString         APPLICATION_NAME;


                    Application(int& argc, char** argv, Logger* logger);
    virtual         ~Application();

    QString         getName();

private:

    Logger*         logger;

    void            displayMessageBox(QString text, QString informativeText);
};

#endif /* APPLICATION_H_ */
