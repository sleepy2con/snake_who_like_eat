//
// Created by lz_fixed on 25-8-16.
//

#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>


class MyGraphicsView final : public QGraphicsView {
    Q_OBJECT

public:
    explicit MyGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

    ~MyGraphicsView() override = default;

protected:
    void wheelEvent(QWheelEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint lastMousePos;
    bool panning = false;
};


#endif //MYGRAPHICSVIEW_H
