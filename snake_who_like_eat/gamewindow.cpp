
#include <QTimer>
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "constant.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
	, ui(new Ui::GameWindow), 
	m_scene(new QGraphicsScene(this)),
    m_gview(new QGraphicsView(m_scene,this))
{
    ui->setupUi(this);
    setCentralWidget(m_gview);
    m_scene->setSceneRect(-100, -100, 200, 200);
	InitTile();
    QTimer::singleShot(0, this, [=]() {m_gview->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding); });
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::InitTile()
{
    //创建一个大小为 TILE_SIZE × TILE_SIZE 的空白 QPixmap
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.setRenderHint(QPainter::Antialiasing, false);
    QPen pen(QColor(0, 128, 255));
    pen.setWidth(1);
    p.setPen(pen);
    // 在 bg 上绘制一个从 (0, 0) 开始、大小为 TILE_SIZE × TILE_SIZE 的矩形
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);
    m_gview->setBackgroundBrush(QBrush(bg));
}
