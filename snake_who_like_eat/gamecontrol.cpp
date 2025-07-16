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
	int w = SCALE_UNIT_SIZE * WIDTH_RATIO;
	int h = SCALE_UNIT_SIZE * HEIGHT_RATIO;

	// 获取场景的实际左上角和右下角坐标
	// 由于你设置了 -w/2, -h/2 作为左上角，所以：
	qreal map_min_x = -1.0 * w / 2.0;
	qreal map_min_y = -1.0 * h / 2.0;
	qreal map_max_x = 1.0 * w / 2.0;
	qreal map_max_y = 1.0 * h / 2.0;

	// 假设食物的大小是 FOOD_SIZE x FOOD_SIZE
	// 如果食物大小也是随机的，你可以在这里先生成它
	qreal actual_food_size = TILE_SIZE; // 或者调用 get_random_food_diameter();

	// 2. 计算食物可以生成的网格范围
	// 食物左上角的 x 坐标必须落在 [map_min_x, map_max_x - actual_food_size] 之间
	// 且必须是 TILE_SIZE 的倍数

	// 计算 X 轴上可以放置食物的瓦片数量（从左到右）
	int num_tiles_x = (map_max_x - actual_food_size - map_min_x) / TILE_SIZE + 1;
	// 计算 Y 轴上可以放置食物的瓦片数量（从上到下）
	int num_tiles_y = (map_max_y - actual_food_size - map_min_y) / TILE_SIZE + 1;

	// 随机选择一个网格索引
	// 注意：这里 generateRandomInt 的范围是 [0, count - 1]
	int random_tile_index_x = generateRandomInt(0, num_tiles_x - 1);
	int random_tile_index_y = generateRandomInt(0, num_tiles_y - 1);

	// 3. 将网格索引转换为实际的场景坐标
	qreal food_x = map_min_x + random_tile_index_x * TILE_SIZE;
	qreal food_y = map_min_y + random_tile_index_y * TILE_SIZE;

	// 4. 创建食物 QGraphicsItem 并添加到场景
	// 假设你有 Food 类，构造函数接收 x, y, size
	 Food* new_food = new Food(food_x, food_y);
	 m_scene.addItem(new_food);

	// 调试输出
	//qDebug() << "食物生成位置: (" << food_x << "," << food_y << "), 尺寸: " << actual_food_size;
}
