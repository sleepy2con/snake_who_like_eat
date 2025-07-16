#ifndef FOOD_H
#define FOOD_H
#include <QGraphicsItem>

#include "constant.h"

class Food : public QGraphicsItem
{
public:
	explicit inline Food(qreal x, qreal y) {
		setPos(x, y);
		//setData(GameObjectsData::GD_Type, GameObjectTypes::GO_Food);
	};
	QRectF boundingRect() const override;
	void paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*) override;

};

#endif // FOOD_H
