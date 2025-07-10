#include <QGraphicsScene>
#include <memory>
#include "gamecontrol.h"
#include "snake.h"
GameControl::GameControl(QGraphicsScene& scene_, QObject* parent_):
	QObject(parent_),
	isPause(0),
	m_snake(new Snake(*this)),
	m_scene(scene_)
{
	m_scene.addItem(m_snake);
	//m_snake = std::make_unique<Snake>(*this);
	//m_snake = std::unique_ptr<Snake>(new Snake(*this));
}
