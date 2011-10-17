#include "SplashScreen.h"

SplashScreen::SplashScreen(const QPixmap& pixmap)
: QSplashScreen(pixmap)
{
    rect      = QRect(10, 477, 500, 500);
    alignment = Qt::AlignLeft;
    color     = QColor(0, 0, 0, 255);
}


SplashScreen::~SplashScreen()
{
}


void SplashScreen::drawContents(QPainter* painter)
{
    QPixmap textPix = QSplashScreen::pixmap();

    painter->setPen(color);
    painter->drawText(this->rect, this->alignment, this->message);
}


void SplashScreen::showStatusMessage(const QString &message, const QColor &color)
{
    this->message = message;
    this->color = color;
    this->showMessage(this->message, this->alignment, this->color);
}
