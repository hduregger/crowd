#ifndef GRAPHICSVIEW_H_
#define GRAPHICSVIEW_H_

#include <QGraphicsView>
#include <QResizeEvent>
#include <QString>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:

    static const float      MOUSE_WHEEL_DELTA;

    static const float      MAXIMUM_ZOOM;
    static const float      MINIMUM_ZOOM;

    static const float      ZOOM_STEP_SIZE;

            GraphicsView(QWidget* parent);
    virtual ~GraphicsView();

    QString getZoomFactorString();

public slots:

    void    zoomOriginal();
    void    zoomIn();
    void    zoomOut();


protected:

    void    resizeEvent(QResizeEvent* event);
    void    wheelEvent(QWheelEvent* event);
    void    mousePressEvent(QMouseEvent* event);
    void    mouseReleaseEvent(QMouseEvent* event);
    void    mouseMoveEvent(QMouseEvent* event);

    void    setZoom(float zoom);

    void    updateDragMode();

    float   zoom;
    float   zoomStep;

signals:

    void    zoomChanged(float zoom);
    void    zoomChanged(QString s);

    void    mousePicked(QPointF position);
    void    mousePickedMinimum(QPointF position);
    void    mousePickedMaximum(QPointF position);
    void    mouseMoved(QPointF position);
    void    mousePainted(QPointF position);

private:

    bool    isDragging;
    bool    isPicking;
    bool    isPainting;

    QPoint  lastMousePosition;

    void    handlePicking(QMouseEvent* event);

    void    handlePickingMinimum(QMouseEvent* event);
    void    handlePickingMaximum(QMouseEvent* event);
    void    handleMovement(QMouseEvent* event);

    void    handlePainting(QMouseEvent* event);
};

#endif /* GRAPHICSVIEW_H_ */
