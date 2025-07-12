#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

class GameControl;
class Snake : public QGraphicsItem
{
public:
	enum class Direction {
		NoMove,
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown
	};
	explicit Snake(GameControl& controller);
	~Snake() = default;
	QRectF boundingRect() const override;
	void paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*) override;
	void 	go_forward();
	void setMoveDirection(Direction);
	void advance(int) override;
private:
	QPointF        m_head;
	GameControl& m_controller;
	Direction m_cur_direction;

};

#endif // SNAKE_H
