#include <QPainter>
#include "../include/food.h"
#include "../include/commhelper.h"

static const qreal FOOD_RADIUS = 3.0;

Food::Food(qreal x, qreal y) :m_x(x),m_y(y){
    setPos(x*TILE_SIZE, y*TILE_SIZE);
    setData(static_cast<int>(GameObjectsData::GD_Type), QVariant::fromValue(GameObjectTypes::GO_Food));
}

QRectF Food::boundingRect() const {
    return shape().boundingRect();
}

void Food::paint(QPainter *p_, const QStyleOptionGraphicsItem *, QWidget *) {
    p_->setBrush(Qt::red); // Set the color of the food
    //p_->drawEllipse(boundingRect()); // Draw a circle for the foodi
    p_->setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing for smoother edges
    p_->setPen(Qt::NoPen);
    // p_->drawRect(TILE_SIZE / 4, TILE_SIZE / 4, TILE_SIZE/2, TILE_SIZE/2);
    // path_.addEllipse(QPointF(TILE_SIZE/2, TILE_SIZE/2), FOOD_RADIUS, FOOD_RADIUS);
    p_->fillPath(shape(), Qt::red);
}

QPainterPath Food::shape() const
{
    QPainterPath path_;
    // 让矩形的左上角变为 (-TILE_SIZE/4, -TILE_SIZE/4)，这样它就居中于(0,0)了
    // path_.addRect(TILE_SIZE / 4, TILE_SIZE / 4, TILE_SIZE/2, TILE_SIZE/2);
    path_.addEllipse(QPointF(TILE_SIZE/2, TILE_SIZE/2), TILE_SIZE/4, TILE_SIZE/4);
    return path_;
}
