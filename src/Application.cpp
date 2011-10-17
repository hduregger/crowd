#include <QMessageBox>

#include "Application.h"
#include "Exception.h"
#include "MainWindow.h"


const   QString         Application::APPLICATION_NAME = "Crowd Simulation 1.0";


Application::Application(int& argc, char** argv, Logger* logger)
:   QApplication(argc, argv),
    logger(logger)
{
}


Application::~Application()
{
}


QString Application::getName()
{
#ifdef DEBUG
    return APPLICATION_NAME + " DEBUG";
#else
    return APPLICATION_NAME;
#endif
}


void Application::displayMessageBox(QString text, QString informativeText)
{
    QMessageBox messageBox;

    messageBox.setText(text);
    messageBox.setInformativeText(informativeText);
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.setWindowTitle(getName());

    messageBox.exec();
}
