#include <QPainter>
#include "snake.h"
#include "constant.h"

static const qreal SNAKE_SIZE = TILE_SIZE;

Snake::Snake(GameControl& controller_) :m_head(0, 0), m_controller(controller_),
m_cur_direction(Direction::NoMove)
{
}

// boundingRect() 返回的矩形是该 QGraphicsItem 的局部坐标系下的包围盒
// 个人理解相当于规定了画布范围, 实际的绘画要由 paint() 函数来做
QRectF Snake::boundingRect() const
{
	// 参数,左上角点 (x, y) 和宽度 width、高度 height 构成
	// 这里规定了paint的绘画区域,(x,y) 是该 Item 本地坐标系中的 (0,0)
	return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
}

void Snake::paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*)
{
	QPainterPath path_;
	path_.setFillRule(Qt::WindingFill);
	//path_.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));
	p_->setBrush(Qt::yellow);
	p_->setPen(Qt::darkYellow);
	// 个人理解, 这里的drawRect的坐标是按照boundingRect()的左上角算的
	p_->drawRect(0, 0, SNAKE_SIZE-1, SNAKE_SIZE-1);
	p_->fillPath(path_, Qt::yellow);
}

void Snake::go_forward()
{
	switch (m_cur_direction)
	{
		case Direction::MoveLeft: {
			m_head.rx() -= TILE_SIZE;
			break;
		}
		case Direction::MoveRight: {
			m_head.rx() += TILE_SIZE;
			break;
		}
		case Direction::MoveUp: {
			m_head.ry() -= TILE_SIZE;
			break;
		}
		case Direction::MoveDown: {
			m_head.ry() += TILE_SIZE;
			break;
		}
		case Direction::NoMove: {
			break;
		}
		default: {
			break;
		}
	}
}

void Snake::setMoveDirection(Direction dir_)
{
	if (m_cur_direction == dir_)
		return;
	if (m_cur_direction == Direction::MoveLeft && dir_ == Direction::MoveRight)
		return;
	if (m_cur_direction == Direction::MoveRight && dir_ == Direction::MoveLeft)
		return;
	if (m_cur_direction == Direction::MoveUp && dir_ == Direction::MoveDown)
		return;
	if (m_cur_direction == Direction::MoveDown && dir_ == Direction::MoveUp)
		return;
	m_cur_direction = dir_;
}

void Snake::advance(int phase_)
{
	if (!phase_)
		return;
	go_forward();
	setPos(m_head);
}
