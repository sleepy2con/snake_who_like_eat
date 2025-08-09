#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QTimer>
#include <memory>

#include <functional>

class QGraphicsScene;
class Snake;
class QKeyEvent;
class Food;
class random_device;
class mt19937;

class GameControl : public QObject {
public:
    // QObject 不能按引用传递, 因为会调用拷贝构造函数, 而它的拷贝构造函数被禁止了
    explicit GameControl(QGraphicsScene &scene_, QObject *parent_);

    ~GameControl() override = default;

    void snakeAteFood(Food *);

    void snakeAteItself();

    void setCallBack(std::function<void(Food *)> cb_);

    void AddPoints(const unsigned int grades_) {
        m_score += grades_;
    }

    [[nodiscard]] unsigned int getScore() const {
        return m_score;
    }
protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    void handleKeyPressed(QKeyEvent *);
    QGraphicsScene &m_scene;
    bool isPause;
    QTimer m_timer;
    Snake *m_snake;
    unsigned int m_score;
    std::function<void(Food *)> cb_ate_food;
};

#endif // GAMECONTROL_H
