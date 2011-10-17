#ifndef SPLASHSCREEN_H_
#define SPLASHSCREEN_H_

#include <QSplashScreen>
#include <QPainter>

class SplashScreen: public QSplashScreen
{
public:
                    SplashScreen(const QPixmap& pixmap);
    virtual         ~SplashScreen();

    virtual void    drawContents(QPainter* painter);
    void            showStatusMessage(const QString& message, const QColor& color = Qt::black);


private:

    QString         message;
    int             alignment;
    QColor          color;
    QRect           rect;

};

#endif /* SPLASHSCREEN_H_ */
