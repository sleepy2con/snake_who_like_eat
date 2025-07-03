#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),m_GameWindow(new GameWindow(this))
{
    ui->setupUi(this);
    m_GameWindow->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_startgame_clicked() {
    QMessageBox::information(0, tr("警告"), tr("hhaa。"));
    m_GameWindow->show();
}
