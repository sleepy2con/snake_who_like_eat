
#include <QTimer>
#include "../include/gamewindow.h"
#include "../ui_gamewindow.h"
#include "../include/constant.h"
#include "../include/gamecontrol.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
	, ui(new Ui::GameWindow), 
	m_scene(new QGraphicsScene(this)),
    m_gview(new QGraphicsView(m_scene,this)),
    m_ctrl(new GameControl(*m_scene,this))
{
    ui->setupUi(this);
    setCentralWidget(m_gview);
	int w = SCALE_UNIT_SIZE * WIDTH_RATIO;
	int h = SCALE_UNIT_SIZE * HEIGHT_RATIO;
    m_scene->setSceneRect(-1 * w /2, -1 * h/2, w, h);
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
    //p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);
    
    // 问题:现在蛇的边界会稍稍偏移左上一点点, 猜测是QGraphicsView绘制地图瓷砖时,
    //由于 QPen 的宽度为 1，QPainter 在绘制 drawRect() 时，笔的中心线位于矩形的边缘。
    p.fillRect(0,0,TILE_SIZE,TILE_SIZE,Qt::gray);
    p.drawLine(TILE_SIZE - 1, 0, TILE_SIZE - 1, TILE_SIZE - 1);
    p.drawLine(0, TILE_SIZE - 1, TILE_SIZE - 1, TILE_SIZE - 1);
    m_gview->setBackgroundBrush(QBrush(bg));
}
