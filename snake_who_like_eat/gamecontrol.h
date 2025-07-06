#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QTimer>
#include <memory>

class QGraphicsScene;
class Snake;

class GameControl:public QObject
{
public:
    // QObject 不能按引用传递, 因为会调用拷贝构造函数, 而它的拷贝构造函数被禁止了
    GameControl(QGraphicsScene& scene_,QObject* parent_);

private:
    QTimer timer;
    QGraphicsScene& m_scene;
    bool isPause;

    // 推迟 m_snake 的初始化,因为m_snake初始化需要GameControl this
    Snake* m_snake;
    //std::unique_ptr<Snake> m_snake;
};

#endif // GAMECONTROL_H
