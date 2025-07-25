#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class GameWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
	void on_btn_startgame_clicked();
private:
    Ui::MainWindow *ui;
	GameWindow* m_GameWindow = nullptr;
};
#endif // MAINWINDOW_H
