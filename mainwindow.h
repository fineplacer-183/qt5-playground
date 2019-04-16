#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void whenButtonPlusIsClicked();
    void whenButtonMinusIsClicked();
    void whenDialIsTurned();

private:
    Ui::MainWindow *ui;
    int counter;
    const int maxCounter = 10;
    const int minCounter = -10;
};

#endif // MAINWINDOW_H
