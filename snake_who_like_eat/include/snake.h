#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>
#include <unordered_set>
#include <deque>
#include <functional>
#include <mutex>

namespace std {
    template<>
    struct hash<QPointF> {
        // 重载函数调用运算符
        size_t operator()(const QPointF &p) const {
            // 将 QPointF 的 x 和 y 坐标组合成一个哈希值
            // 使用 std::hash<qreal> 来哈希 x 和 y
            size_t h1 = std::hash<qreal>()(p.x());
            size_t h2 = std::hash<qreal>()(p.y());

            // 这是一个常用的哈希组合技巧，可以有效减少冲突
            // 0x9e3779b9 是一个魔法数字，常用于哈希组合
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
}

class GameControl;

class Snake : public QGraphicsItem {
public:
    enum class Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    explicit Snake(GameControl &controller);

    ~Snake() override = default;

    QRectF boundingRect() const override;

    void paint(QPainter *p_, const QStyleOptionGraphicsItem *, QWidget *) override;

    void go_forward();

    void setMoveDirection(Direction);

    ///@brief QGraphicsScene会在自己的advance触发时,同时调用每个内容item的advance,这里重写
    void advance(int) override;

private:
    bool isUTurn(Direction dir_);

    void handleCollision();

    int m_speed;
    unsigned int m_tick_count;

    QPointF m_head;
    GameControl &m_controller;
    Direction m_cur_direction;
    int directions_size; // 设置最大指令队列长度,超出则丢弃
    std::deque<Direction> m_next_dirs; // 记录下一步的方向指令队列
    std::deque<QPointF> m_tail; // 存储身体在scene中的点坐标
    std::unordered_set<QPointF> m_tail_set; // 用来判断蛇头是否撞蛇尾的哈希表
    int m_growing;
    std::mutex m_mutex;
};

#endif // SNAKE_H
