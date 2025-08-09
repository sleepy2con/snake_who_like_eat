#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>

#include "commhelper.h"

namespace Ui {
	class GameWindow;
}

class GameControl;
class Food;
class RandomGenerator;
class QLabel;

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit GameWindow(QWidget* parent = nullptr);
	~GameWindow() override;
	// 设置每一个地图瓷砖,
	void InitTile();
	void InitStatusBar();
	void InitCallBack();
	void AddFood();
private:
	Ui::GameWindow* ui;
	// 成员变量的初始化顺序是由它们在类定义（即头文件.h 文件）中声明的顺序决定的，
	// 而不是由构造函数初始化列表中的顺序决定的
	QGraphicsScene* m_scene;
	QGraphicsView* m_gview;
	int m_map_width;
	int m_map_height;
	QPixmap bg;
	GameControl* m_ctrl;
	RandomGenerator random_generator_;
	QLabel* cur_score;
	// QGraphicsSimpleTextItem* m_gameOverText;
};

#endif // GAMEWINDOW_H
