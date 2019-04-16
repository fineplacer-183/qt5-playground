#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QChart>
#include <QBarSet>
#include <QHorizontalBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->buttonPlus, SIGNAL(clicked()), this, SLOT(whenButtonPlusIsClicked()));
    connect(ui->buttonMinus, SIGNAL(clicked()), this, SLOT(whenButtonMinusIsClicked()));
    connect(ui->dial, SIGNAL(sliderReleased()), this, SLOT(whenDialIsTurned()));
    ui->dial->setMaximum(maxCounter);
    ui->dial->setMinimum(minCounter);
    
    // the following connect is cuerrently set in mainwindwo.ui (designer-qt5)
    // connect(ui->actionQuit, &QAction::triggered, qApp, QApplication::quit);

    setUpChart();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whenButtonPlusIsClicked()
{
    qInfo() << "buttonPlusIsClicked: " << counter;
    if (counter < maxCounter) {
        ui->lcdNumber->display(++counter);
        ui->dial->setValue(counter);
    }
}

void MainWindow::whenButtonMinusIsClicked()
{
    qInfo() << "buttonMinusIsClicked: " << counter;
    if (counter > minCounter) {
        ui->lcdNumber->display(--counter);
        ui->dial->setValue(counter);
    }
}

void MainWindow::whenDialIsTurned()
{
    int val = ui->dial->value();
    qInfo() << "dialIsTurned, value: " << val;
    
    counter = val;
    
    if (counter > maxCounter) {
        counter = maxCounter;
    } else if (counter < minCounter) {
        counter = minCounter;
    }

    ui->lcdNumber->display(counter);
}


void MainWindow::setUpChart()
{
    using namespace QtCharts;
    
    // The bar sets are used in the same way in all bar charts. 
    // To illustrate the difference between various bar charts, 
    // we use the same data in all examples. Data that bar chart visualizes, 
    // is defined by QBarSet instances. Here we create the sets and append data to them. 
    // The data is appended here with << operator. 
    // Alternatively, the append method could also be used.
    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    // We create the series and append the bar sets to it. 
    // The series takes ownership of the barsets. 
    // The series groups the data from sets to categories. 
    // The first values of each set are grouped together in the first category; 
    // the second values in the second category, and so on.
    QHorizontalBarSeries *series = new QHorizontalBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    // Here we create the chart object and add the series to it. 
    // We set the title for chart with setTitle and then turn on 
    // animations of the series by calling setAnimationOptions(QChart::SeriesAnimations).
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple horizontal barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisX->applyNiceNumbers();

    // We also want to show the legend. To do so, we get the legend pointer from chart 
    // and set it to visible. We also place the legend to the bottom of the chart by 
    // setting its alignment to Qt::AlignBottom.
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setChart(chart);

}