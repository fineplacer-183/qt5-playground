#ifndef FPCHART_H
#define FPCHART_H

#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QBarSet>
#include <QHorizontalBarSeries>
#include <QCategoryAxis>

using namespace QtCharts;
class FpChart : public QChartView
{
  Q_OBJECT

public:
  explicit FpChart(QChartView *parent = nullptr);
  ~FpChart();

private:
  QChartView *ui;

private:
 QCategoryAxis *axisX;
 QCategoryAxis *axisY;

private:
  QTimer chartTimer;
  QLineSeries *hotAirData = nullptr;
  QChart *hotAirChart;

public:
  void addDataPoint(QPointF point);

private:
  void setUpChart();

private slots:
  void updateChart();

public slots:
    void handleTimeout();

private:
  QBasicTimer timer;
  QString text;
  int step;
  qreal m_step;
  qreal m_x;
  qreal m_y;
};

#endif // FPCHART_H