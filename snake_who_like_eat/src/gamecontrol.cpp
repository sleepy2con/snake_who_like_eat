#include "../include/gamecontrol.h"
#include "snake.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <random>
#include <chrono>
#include <utility>

#include "../include/food.h"
#include "../include/commhelper.h"
//#include <memory>

GameControl::GameControl(QGraphicsScene &scene_, QObject *parent_)
    : QObject(parent_),
      isPause(false),
      m_snake(new Snake(*this)), //this表示Gamecontrol*,*this表示Gamecontrol&,&this表示GameControl**
      m_scene(scene_) {
    //m_snake = std::unique_ptr<Snake>(new Snake(*this));
    m_scene.addItem(m_snake);
    // 关键步骤：将 GameControl 实例安装到 m_scene 上,这步才能允许gamecontrol捕获事件
    m_scene.installEventFilter(this);
    m_timer.start(1000 / 33);
    connect(&m_timer, &QTimer::timeout, &m_scene, &QGraphicsScene::advance);
}

void GameControl::snakeAteFood(Food *f) {
    // m_scene.removeItem(f);
    addNewFood(f);
}

void GameControl::snakeAteItself() {
    // 一次性定时器
    QTimer::singleShot(0, this, [this]() {
        disconnect(&m_timer, &QTimer::timeout, &m_scene, &QGraphicsScene::advance);
        // exit(0);
        QMessageBox::StandardButton reply = QMessageBox::information(nullptr, "游戏结束", "你死了,要重来吗",
                                                                     QMessageBox::Yes | QMessageBox::No,
                                                                     QMessageBox::Yes);
        if (reply == QMessageBox::Yes) {
            connect(&m_timer, &QTimer::timeout, &m_scene, &QGraphicsScene::advance);
            m_scene.clear();
            m_snake = new Snake(*this);
            m_scene.addItem(m_snake);
            addNewFood(nullptr);
        }
    });
}

void GameControl::setCallBack(std::function<void(Food *)> cb_) {
    cb_ate_food = std::move(cb_);
}

bool GameControl::eventFilter(QObject *obj_, QEvent *e_) {
    if (e_->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *) e_);
        return 1;
    }
    return false;
}

void GameControl::handleKeyPressed(QKeyEvent *e_) {
    switch (e_->key()) {
        case Qt::Key_Up:
        case Qt::Key_W: {
            m_snake->setMoveDirection(Snake::Direction::MoveUp);
            break;
        }
        case Qt::Key_Down:
        case Qt::Key_S: {
            m_snake->setMoveDirection(Snake::Direction::MoveDown);
            break;
        }
        case Qt::Key_Left:
        case Qt::Key_A: {
            m_snake->setMoveDirection(Snake::Direction::MoveLeft);
            break;
        }
        case Qt::Key_Right:
        case Qt::Key_D: {
            m_snake->setMoveDirection(Snake::Direction::MoveRight);
            break;
        }
        case Qt::Key_Space: {
            m_snake->setMoveDirection(Snake::Direction::NoMove);
            break;
        }
        default:
            break;
    }
}

void GameControl::addNewFood(Food* f) {
    qDebug() << "exec addNewFood" ;
    if (cb_ate_food) {
        this->cb_ate_food(f);
    }
}
