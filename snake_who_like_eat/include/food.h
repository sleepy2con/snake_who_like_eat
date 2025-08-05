#ifndef FOOD_H
#define FOOD_H
#include <QGraphicsItem>

#include "constant.h"

class Food : public QGraphicsItem
{
public:
	Food(qreal x, qreal y);
	QRectF boundingRect() const override;
	void paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*) override;

};

#endif // FOOD_H
