#ifndef FPCHART_H
#define FPCHART_H

#include <QWidget>
#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QBarSet>

using namespace QtCharts;
class FpChart : public QChartView
{
  Q_OBJECT

public:
  explicit FpChart(QChartView *parent = nullptr);

private:
  QChartView *ui;

private:
  QTimer *chartTimer;
  QBarSet *set0;
  QBarSet *set1;
  QBarSet *set2;
  QBarSet *set3;
  QBarSet *set4;

private:
  void setUpChart();

private slots:
  void updateChart();

private:
  QBasicTimer timer;
  QString text;
  int step;
};

#endif // FPCHART_H