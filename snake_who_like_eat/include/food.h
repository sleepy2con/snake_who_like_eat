#ifndef FOOD_H
#define FOOD_H
#include <QGraphicsItem>

#include "constant.h"

class Food : public QGraphicsItem
{
public:
	Food(qreal x, qreal y);
	// 表示这个返回值必须要被使用，否则会报错
	[[nodiscard]] QRectF boundingRect() const override;
	void paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*) override;
	QPainterPath shape() const override;
private:
	qreal m_x;
	qreal m_y;
};

#endif // FOOD_H
