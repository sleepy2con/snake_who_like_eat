#include "gamecontrol.h"
#include "snake.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include "food.h"
#include "commhelper.h" // for generateRandomInt
//#include <memory>

GameControl::GameControl(QGraphicsScene& scene_, QObject* parent_) :
	QObject(parent_),
	isPause(0),
	m_snake(new Snake(*this)),	//this表示Gamecontrol*,*this表示Gamecontrol&,&this表示GameControl**
	m_scene(scene_)
{
	//m_snake = std::unique_ptr<Snake>(new Snake(*this));
	m_scene.addItem(m_snake);
	addNewFood();
	// 关键步骤：将 GameControl 实例安装到 m_scene 上,这步才能允许gamecontrol捕获事件
	m_scene.installEventFilter(this);
	m_timer.start(1000 / 33);
    connect(&m_timer, &QTimer::timeout, &m_scene, &QGraphicsScene::advance);
}

bool GameControl::eventFilter(QObject* obj_, QEvent* e_)
{
	if (e_->type() == QEvent::KeyPress)
	{
		handleKeyPressed((QKeyEvent*)e_);
		return 1;
	}
	return false;
}

void GameControl::handleKeyPressed(QKeyEvent* e_)
{
	switch (e_->key()) {
		case Qt::Key_Up:
		case Qt::Key_W: {
			m_snake->setMoveDirection(Snake::Direction::MoveUp);
			break;
		}
		case Qt::Key_Down:
		case Qt::Key_S:
		{
			m_snake->setMoveDirection(Snake::Direction::MoveDown);
			break;
		}
		case Qt::Key_Left:
		case Qt::Key_A:
		{
			m_snake->setMoveDirection(Snake::Direction::MoveLeft);
			break;
		}
		case Qt::Key_Right:
		case Qt::Key_D:
		{
			m_snake->setMoveDirection(Snake::Direction::MoveRight);
			break;
		}
		case Qt::Key_Space:
		{
			m_snake->setMoveDirection(Snake::Direction::NoMove);
			break;
		}
		default:
			break;
	}

}

void GameControl::addNewFood()
{
	// 1. 获取地图的实际宽度和高度
	// 注意：这里的 w 和 h 是你设置 sceneRect 时的参数
	// 如果 w 和 h 是成员变量或常量，直接使用即可
	int w = SCALE_UNIT_SIZE * WIDTH_RATIO;		// 50 * 16 = 800
	int h = SCALE_UNIT_SIZE * HEIGHT_RATIO;		// 50 * 9 = 450

	int x, y;
	// (0 - 80 ) - 40 = -40 ~ 40
	x = (std::rand() % w / 10 - (w / 10) / 2);
	x *= 10;
	y = std::rand() % h / 10 - (h / 10) / 2;
	y *= 10;
	//x = generateRandomInt(-w / 2, w / 2);
	//y = generateRandomInt(-h / 2, h / 2);

	// 假设你有 Food 类，构造函数接收 x, y, size
	 Food* new_food = new Food(x,y);
	 m_scene.addItem(new_food);

	// 调试输出
	//qDebug() << "食物生成位置: (" << food_x << "," << food_y << "), 尺寸: " << actual_food_size;
}
