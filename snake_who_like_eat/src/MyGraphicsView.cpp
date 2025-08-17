// MyGraphicsView.cpp
#include "MyGraphicsView.h"
#include <QDebug>
#include <qevent.h>

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    // TODO 写一个拖拽和滚轮缩放地图功能
    setRenderHints(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::NoAnchor);
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    constexpr double scaleFactor = 1.15;
    double factor = (event->angleDelta().y() > 0) ? scaleFactor : 1.0 / scaleFactor;

    // 限制缩放比例
    qreal currentScale = transform().m11();
    if ((currentScale > 5.0 && factor > 1.0) || (currentScale < 0.2 && factor < 1.0))
        return;

    // 鼠标位置对应的 scene 坐标（缩放前）
    QPointF mouseScenePos = mapToScene(event->position().toPoint());

    // 执行缩放
    scale(factor, factor);

    // 缩放后鼠标对应的 scene 坐标
    QPointF mouseScenePosAfter = mapToScene(event->position().toPoint());

    // 计算 delta 并平移视图矩阵
    QPointF delta = mouseScenePos - mouseScenePosAfter;
    if (!delta.isNull())
        translate(delta.x(), delta.y());
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        panning = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        panning = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (panning) {
        QPointF delta = mapToScene(lastMousePos) - mapToScene(event->pos());
        lastMousePos = event->pos();
        centerOn(mapToScene(viewport()->rect().center()) + delta);
    }
    QGraphicsView::mouseMoveEvent(event);
}
