#include <QPainter>

#include "food.h"
#include "commhelper.h"

QRectF Food::boundingRect() const {
	int random_size = generateRandomInt(TILE_SIZE / 3, TILE_SIZE);
	return QRectF(0, 0, TILE_SIZE / 2, TILE_SIZE / 2); // Example size, adjust as needed
}

void Food::paint(QPainter* p_, const QStyleOptionGraphicsItem*, QWidget*) {
	p_->setBrush(Qt::red); // Set the color of the food
	p_->drawEllipse(boundingRect()); // Draw a circle for the food
}