#include <QTimer>
#include <QLabel>

#include "../include/gamewindow.h"
#include "../ui_gamewindow.h"
#include "constant.h"
#include "gamecontrol.h"
#include "food.h"
#include "commhelper.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::GameWindow)
      , m_scene(new QGraphicsScene(this))
      , m_gview(new QGraphicsView(m_scene, this))
      , m_ctrl(new GameControl(*m_scene, this))
      , random_generator_()
      , m_map_width(SCALE_UNIT_SIZE * WIDTH_RATIO)
      , m_map_height(SCALE_UNIT_SIZE * HEIGHT_RATIO)
// , m_gameOverText(new QGraphicsSimpleTextItem("你死了", m_scene))
{
    ui->setupUi(this);
    setCentralWidget(m_gview);
    InitCallBack();
    m_scene->setSceneRect(-1 * m_map_width / 2, -1 * m_map_height / 2, m_map_width, m_map_height);
    InitTile();
    InitUI();
    QTimer::singleShot(0, this, [=]() { m_gview->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding); });
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::InitTile() {
    //创建一个大小为 TILE_SIZE × TILE_SIZE 的空白 QPixmap画布瓷砖,setBackgroundBrush 会用这个模板来填充整个 QGraphicsView 的背景，
    QPixmap _tile(TILE_SIZE, TILE_SIZE);
    // 绑定在这个QPixmap瓷砖上,画笔p会在这个瓷砖上绘画
    QPainter p(&_tile);
    p.setBrush(QBrush(Qt::gray));
    p.setRenderHint(QPainter::Antialiasing, false);
    QPen pen(QColor(0, 128, 255));
    pen.setWidth(1);
    p.setPen(pen);
    // 在 bg 上绘制一个从 (0, 0) 开始、大小为 TILE_SIZE × TILE_SIZE 的矩形
    //p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    // 问题:现在蛇的边界会稍稍偏移左上一点点, 猜测是QGraphicsView绘制地图瓷砖时,
    //由于 QPen 的宽度为 1，QPainter 在绘制 drawRect() 时，笔的中心线位于矩形的边缘。
    p.fillRect(0, 0, TILE_SIZE, TILE_SIZE, Qt::gray);
    p.drawLine(TILE_SIZE - 1, 0, TILE_SIZE - 1, TILE_SIZE - 1);
    p.drawLine(0, TILE_SIZE - 1, TILE_SIZE - 1, TILE_SIZE - 1);
    m_gview->setBackgroundBrush(QBrush(_tile));
    AddFood();
}

void GameWindow::InitUI() {
    QStatusBar *statusBar = this->statusBar();
    auto *leftLabel = new QLabel(QString("宽: %1 ,高: %2 ").arg(m_map_width).arg(m_map_height));
    statusBar->addWidget(leftLabel);
}

void GameWindow::InitCallBack() {
    m_ctrl->setCallBack([this](Food *f) {
        if (f) {
            qDebug() << "Food was eat";
            m_scene->removeItem(f);
        }
        AddFood();
    });
}

void GameWindow::AddFood() {
    int x = random_generator_.getInt(-m_map_width / 2, m_map_width / 2);
    int y = random_generator_.getInt(-m_map_height / 2, m_map_height / 2);
    auto food = new Food(x, y);
    qDebug() << "Food created at:" << x << "," << y;
    m_scene->addItem(food);
}
