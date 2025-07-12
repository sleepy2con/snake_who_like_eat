#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QTimer>
#include <memory>

class QGraphicsScene;
class Snake;
class QKeyEvent;

class GameControl:public QObject
{
public:
    // QObject 不能按引用传递, 因为会调用拷贝构造函数, 而它的拷贝构造函数被禁止了
    explicit GameControl(QGraphicsScene& scene_,QObject* parent_);
    ~GameControl() = default;
protected:
    bool eventFilter(QObject*, QEvent*);

private:
    void handleKeyPressed(QKeyEvent*);

    QGraphicsScene& m_scene;
    bool isPause;
    QTimer m_timer;
    // 推迟 m_snake 的初始化,因为m_snake初始化需要GameControl this
    //std::unique_ptr<Snake> m_snake;
    Snake* m_snake;
};

#endif // GAMECONTROL_H
