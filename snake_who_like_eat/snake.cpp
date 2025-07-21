#include <QPainter>
#include "snake.h"
#include "constant.h"
#include "food.h"
#include "gamecontrol.h"

static const qreal SNAKE_SIZE = TILE_SIZE;

Snake::Snake(GameControl& controller_) :
	m_head(0, 0),
	m_controller(controller_),
	m_cur_direction(Direction::NoMove),
	m_tick_count(0),
	m_speed(5),
	directions_size(5),
	m_growing(4)
{

}

// boundingRect() 返回的矩形是该 QGraphicsItem 的局部坐标系下的包围盒
// 个人理解相当于规定了画布范围, 实际的绘画要由 paint() 函数来做
QRectF Snake::boundingRect() const
{
	// 参数,左上角点 (x, y) 和宽度 width、高度 height 构成
	// 这里规定了paint的绘画区域,(x,y) 是该 Item 本地坐标系中的 (0,0)
	qreal minX = m_head.x(), minY = m_head.y();
	qreal maxX = m_head.x(), maxY = minY;

	for (auto& t : m_tail)
	{
		minX = std::min(minX, t.x());
		minY = std::min(minY, t.y());
		maxX = std::max(maxX, t.x());
		maxY = std::max(maxY, t.y());
	}
	QPointF t1 = mapFromScene(QPointF(minX,minY));
	QPointF br = mapFromScene(QPointF(maxX, maxY));
	QRectF rect_(t1.x(), t1.y(), 
		br.x() - t1.x() + TILE_SIZE, 
		br.y() - t1.y() + TILE_SIZE);
	//return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
	return rect_;
}

void Snake::paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*)
{
	p_->save();
	QPainterPath path_;
	path_.setFillRule(Qt::WindingFill);
	//path_.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));
	p_->setBrush(Qt::yellow);
	p_->setPen(Qt::green);
	// 个人理解, 这里的drawRect的坐标是按照boundingRect()的左上角算的
	// 蛇头
	p_->drawRect(0, 0, SNAKE_SIZE - 1, SNAKE_SIZE - 1);
	// 蛇身
	for(auto& t : m_tail)
	{
		QPointF cur_tail_pos = mapFromScene(t);
		path_.addRect(cur_tail_pos.x(), cur_tail_pos.y(), SNAKE_SIZE - 1, SNAKE_SIZE - 1);
	}
	p_->fillPath(path_, Qt::yellow);
	p_->restore();
}

void Snake::go_forward()
{
	// 没五次调用一次前进,速度越大越慢
	if (m_tick_count++ % m_speed !=0)
		return;
	while (!m_next_dirs.empty())
	{
		if (isUTurn(m_next_dirs.front()))
		{
			m_cur_direction = m_next_dirs.front();
			m_next_dirs.pop_front();
			break;
		}
		m_next_dirs.pop_front();
	}
	if(m_cur_direction == Direction::NoMove)
		return;
	//当蛇头移动时，它原来的位置就变成了新的身体节，而蛇尾的最后一节则会消失（如果蛇没有增长）。
	// 把旧的蛇头的位置存进来，当作新的蛇身
	m_tail.push_front(m_head);
	m_tail_set.insert(m_head);
	if (m_growing > 0)
		m_growing--;
	else
	{
		if (m_tail_set.count(m_tail.back()) > 0)
		{
			m_tail_set.erase(m_tail.back());
		}
		m_tail.pop_back();
	}
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
		default: {
			break;
		}
	}
}

void Snake::setMoveDirection(Direction dir_)
{
	while (m_next_dirs.size() >= directions_size)
	{
		m_next_dirs.pop_front();
	}
	m_next_dirs.push_back(dir_);
	if (m_cur_direction == dir_ ||
		m_cur_direction == Direction::MoveLeft && dir_ == Direction::MoveRight ||
		m_cur_direction == Direction::MoveRight && dir_ == Direction::MoveLeft ||
		m_cur_direction == Direction::MoveUp && dir_ == Direction::MoveDown ||
		m_cur_direction == Direction::MoveDown && dir_ == Direction::MoveUp)
		return;
	m_cur_direction = dir_;
}

void Snake::advance(int phase_)
{
	if (!phase_)
		return;

	go_forward();
	setPos(m_head);
	handleCollision();
}

bool Snake::isUTurn(Direction dir_)
{
	if (m_cur_direction == dir_ ||
		m_cur_direction == Direction::MoveLeft && dir_ == Direction::MoveRight ||
		m_cur_direction == Direction::MoveRight && dir_ == Direction::MoveLeft ||
		m_cur_direction == Direction::MoveUp && dir_ == Direction::MoveDown ||
		m_cur_direction == Direction::MoveDown && dir_ == Direction::MoveUp)
		return false;
	return true;
}

void Snake::handleCollision()
{
	QList<QGraphicsItem*> colloions = collidingItems();
	for(auto & item : colloions)
	{
		if (item->data(static_cast<int>(GameObjectsData::GD_Type)).value<GameObjectTypes>() == GameObjectTypes::GO_Food)
		{
			m_growing++; // 吃到食物后, 蛇长大
			m_controller.snakeAteFood((Food*)(item));
		}
	}
	if (m_tail_set.count(m_head) > 0)
	{
		m_controller.snakeAteItself();
	}
}
