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

protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    void handleKeyPressed(QKeyEvent *);

    void addNewFood(Food* f);


    QGraphicsScene &m_scene;
    bool isPause;
    QTimer m_timer;
    Snake *m_snake;

    std::function<void(Food *)> cb_ate_food;
};

#endif // GAMECONTROL_H
