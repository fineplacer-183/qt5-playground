#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fpchart.h>

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
    int counter = 0;
    int changeCount = 0;
    const int maxCounter = 10;
    const int minCounter = -10;
    FpChart *chart;
};

#endif // MAINWINDOW_H
