#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

class GameControl;
class Snake : public QGraphicsItem
{
public:
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };
    Snake(GameControl& controller);
    QRectF boundingRect() const;
    void paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*);
    void 	go_forward();
private:
    QPointF        m_head;
	GameControl& m_controller;
};

#endif // SNAKE_H
