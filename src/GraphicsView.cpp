#include "GraphicsView.h"
#include "Number.h"

#include <QScrollBar>

const float     GraphicsView::MOUSE_WHEEL_DELTA = 120.0f;

const float     GraphicsView::MAXIMUM_ZOOM      =  15.0f;
const float     GraphicsView::MINIMUM_ZOOM      =   0.2f;

const float     GraphicsView::ZOOM_STEP_SIZE    =   0.2f;


GraphicsView::GraphicsView(QWidget* parent)
:   QGraphicsView(parent),
    zoom(1.0f),
    isDragging(false),
    isPicking(false),
    isPainting(false)
{
}

GraphicsView::~GraphicsView()
{
}


void GraphicsView::zoomOriginal()
{
    zoom = 1.0f;
    setZoom(zoom);
}


QString GraphicsView::getZoomFactorString()
{
    return QString::number(zoom, 'f', 1) + "x";
}


void GraphicsView::setZoom(float z)
{
    zoom = NumberTemplate<float>::clamp(MINIMUM_ZOOM, MAXIMUM_ZOOM, z);

    // NOTE:
    // Something in the current zoom design with Qt view/scene or with glViewport is buggy.
    // Zooms above certain levels depending on scene size, cause the scene to scroll.
    // The Qt view/scene design is difficult to understand, the documentation is misleading,
    // and things don't behave as expected.
    // Attempts to fix it took too long, so we just limit maximum zoom as a work around.

    setTransform(QTransform::fromScale(zoom, zoom), false);

    emit zoomChanged(zoom);
    emit zoomChanged(getZoomFactorString());
}


void GraphicsView::zoomIn()
{
    setZoom(zoom + ZOOM_STEP_SIZE);
}


void GraphicsView::zoomOut()
{
    setZoom(zoom - ZOOM_STEP_SIZE);
}


void GraphicsView::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
}


void GraphicsView::wheelEvent(QWheelEvent* event)
{
    if (event->orientation() == Qt::Vertical)
    {
        setZoom(zoom + event->delta() / MOUSE_WHEEL_DELTA * ZOOM_STEP_SIZE);

        event->accept();
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}


void GraphicsView::handlePickingMinimum(QMouseEvent* event)
{
    QPointF position = mapToScene(event->pos());

    emit mousePickedMinimum(position);
    emit mousePicked(position);
}


void GraphicsView::handlePickingMaximum(QMouseEvent* event)
{
    QPointF position = mapToScene(event->pos());

    emit mousePickedMaximum(position);
    emit mousePicked(position);
}


void GraphicsView::handlePicking(QMouseEvent* event)
{
    QPointF position = mapToScene(event->pos());

    emit mousePicked(position);
}


void GraphicsView::handlePainting(QMouseEvent* event)
{
    QPointF position = mapToScene(event->pos());

    emit mousePainted(position);
}


void GraphicsView::handleMovement(QMouseEvent* event)
{
    QPointF position = mapToScene(event->pos());

    emit mouseMoved(position);
}


void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        isDragging = true;

        lastMousePosition = event->pos();

        event->accept();
    }
    else if (event->button() == Qt::LeftButton)
    {
        isPicking = true;

        if (event->modifiers().testFlag(Qt::ShiftModifier))
        {
            handlePickingMaximum(event);
        }
        else if (event->modifiers().testFlag(Qt::ControlModifier))
        {
            handlePickingMinimum(event);
        }
        else
        {
            handlePicking(event);
        }

        event->accept();
    }
    else if (event->button() == Qt::MiddleButton)
    {
        isPainting = true;

        handlePainting(event);
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }

}


void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        setDragMode(QGraphicsView::NoDrag);
        isDragging = false;

        event->accept();
    }
    else if (event->button() == Qt::LeftButton)
    {
        isPicking = false;

        event->accept();
    }
    else if (event->button() == Qt::MiddleButton)
    {
        isPainting = false;
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}


void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    handleMovement(event);

    if (isDragging)
    {
        QPoint offset = event->pos() - lastMousePosition;

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - offset.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - offset.y());

        lastMousePosition = event->pos();
    }
    else if (isPicking)
    {
        if (event->modifiers().testFlag(Qt::ShiftModifier))
        {
            handlePickingMaximum(event);
        }
        else if (event->modifiers().testFlag(Qt::ControlModifier))
        {
            handlePickingMinimum(event);
        }
        else
        {
            handlePicking(event);
        }
    }
    else if (isPainting)
    {
        handlePainting(event);
    }

    event->accept();
}


