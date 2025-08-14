#include <QPainter>
#include "../include/food.h"
#include "../include/commhelper.h"

static const qreal FOOD_RADIUS = 3.0;

Food::Food(qreal x, qreal y) :m_x(x),m_y(y){
    // TODO 食物会显示在地图网格边界处，可能同时在两三个网格中，考虑修改下
    setPos(x*TILE_SIZE, y*TILE_SIZE);
    setData(static_cast<int>(GameObjectsData::GD_Type), QVariant::fromValue(GameObjectTypes::GO_Food));
}

QRectF Food::boundingRect() const {
    return {0, 0, TILE_SIZE/2, TILE_SIZE/2}; // Example size, adjust as needed
}

void Food::paint(QPainter *p_, const QStyleOptionGraphicsItem *, QWidget *) {
    p_->setBrush(Qt::red); // Set the color of the food
    //p_->drawEllipse(boundingRect()); // Draw a circle for the foodi
    p_->setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing for smoother edges
    QPainterPath path_;
    p_->drawRect(0, 0, TILE_SIZE/2, TILE_SIZE/2);
    // path_.addEllipse(QPointF(TILE_SIZE/2, TILE_SIZE/2), FOOD_RADIUS, FOOD_RADIUS);
    p_->fillPath(path_, Qt::red);
}
