#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

#include <deque>

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
	bool isUTurn(Direction dir_);

	int m_speed;
	unsigned int m_tick_count;

	QPointF        m_head;
	GameControl& m_controller;
	Direction m_cur_direction;
	int directions_size;	// 设置指令队列长度
	std::deque<Direction> m_next_dirs; // 记录下一步的方向指令
	std::deque<QPointF> m_tail;

	int m_growing;
};

#endif // SNAKE_H
