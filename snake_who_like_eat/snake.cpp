#include <QPainter>
#include "snake.h"
#include "constant.h"

static const qreal SNAKE_SIZE = TILE_SIZE;

Snake::Snake(GameControl& controller_) :m_head(0, 0), m_controller(controller_) {
}

// boundingRect() 返回的矩形是该 QGraphicsItem 的局部坐标系下的包围盒
QRectF Snake::boundingRect() const
{
	// 左上角点 (x, y) 和宽度 width、高度 height 构成
	return QRectF(m_head.x(), m_head.x(), TILE_SIZE, TILE_SIZE);
}

void Snake::paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*)
{
	QPainterPath path_;
	path_.setFillRule(Qt::WindingFill);
	path_.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));
	p_->fillPath(path_, Qt::yellow);
}
