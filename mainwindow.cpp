#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->buttonPlus, SIGNAL(clicked()), this, SLOT(whenButtonPlusIsClicked()));
  connect(ui->buttonMinus, SIGNAL(clicked()), this, SLOT(whenButtonMinusIsClicked()));
  connect(ui->dial, SIGNAL(sliderReleased()), this, SLOT(whenDialIsTurned()));

  // set the Max- and the Minimum for te dial
  ui->dial->setMaximum(maxCounter);
  ui->dial->setMinimum(minCounter);

  // the following connect is cuerrently set in mainwindwo.ui (designer-qt5)
  // connect(ui->actionQuit, &QAction::triggered, qApp, QApplication::quit);
  chart = new FpChart(ui->graphicsView);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::whenButtonPlusIsClicked()
{
  qInfo() << "buttonPlusIsClicked: " << counter;
  if (counter < maxCounter)
  {
    ui->lcdNumber->display(++counter);
    ui->dial->setValue(counter);
  }
  chart->addDataPoint(QPointF(changeCount++, counter));
}

void MainWindow::whenButtonMinusIsClicked()
{
  qInfo() << "buttonMinusIsClicked: " << counter;
  if (counter > minCounter)
  {
    ui->lcdNumber->display(--counter);
    ui->dial->setValue(counter);
  }
  chart->addDataPoint(QPointF(changeCount++, counter));
}

void MainWindow::whenDialIsTurned()
{
  int val = ui->dial->value();
  qInfo() << "dialIsTurned, value: " << val;

  counter = val;

  if (counter > maxCounter)
  {
    counter = maxCounter;
  }
  else if (counter < minCounter)
  {
    counter = minCounter;
  }

  ui->lcdNumber->display(counter);

  chart->addDataPoint(QPointF(changeCount++, counter));
}
