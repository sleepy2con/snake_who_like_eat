#include <QPainter>
#include "../include/food.h"
#include "../include/commhelper.h"

static const qreal FOOD_RADIUS = 3.0;

Food::Food(qreal x, qreal y)
{
	setPos(x, y);
	setData(static_cast<int>(GameObjectsData::GD_Type), QVariant::fromValue(GameObjectTypes::GO_Food));
}

QRectF Food::boundingRect() const {
	return {-TILE_SIZE, -TILE_SIZE, TILE_SIZE * 2, TILE_SIZE * 2}; // Example size, adjust as needed
}

void Food::paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*) {
	p_->setBrush(Qt::red); // Set the color of the food
	//p_->drawEllipse(boundingRect()); // Draw a circle for the foodi 
	p_->setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing for smoother edges
	QPainterPath path_;
	path_.addEllipse(QPointF(TILE_SIZE / 2, TILE_SIZE / 2), FOOD_RADIUS, FOOD_RADIUS);
	p_->fillPath(path_, Qt::red);
}