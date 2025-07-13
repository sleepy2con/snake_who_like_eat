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
	int m_speed;
	unsigned int m_tick_count;

	QPointF        m_head;
	GameControl& m_controller;
	Direction m_cur_direction;
	QList<QPointF> m_tail;

};

#endif // SNAKE_H
