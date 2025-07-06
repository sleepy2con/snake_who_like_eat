#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

namespace Ui {
class GameWindow;
}

class GameControl;
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    // 设置每一个地图瓷砖,
    void InitTile();

private:
    Ui::GameWindow *ui;
    // 成员变量的初始化顺序是由它们在类定义（即头文件.h 文件）中声明的顺序决定的，
    // 而不是由构造函数初始化列表中的顺序决定的
    QGraphicsScene* m_scene;
    QGraphicsView* m_gview;
    QPixmap bg;
    GameControl* m_ctrl;
};

#endif // GAMEWINDOW_H
