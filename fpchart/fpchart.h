#ifndef FPCHART_H
#define FPCHART_H

#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QCategoryAxis>

using namespace QtCharts;

class FpChart : public QChartView
{
  Q_OBJECT

public:
  explicit FpChart(QChartView *parent = nullptr);
  ~FpChart();

private:
  QChartView *ui = nullptr;

private:
 QCategoryAxis *axisX = nullptr;
 QCategoryAxis *axisY = nullptr;

private:
  QTimer chartTimer;
  QLineSeries *hotAirData = nullptr;
  QChart *hotAirChart = nullptr;

public:
  void addDataPoint(QPointF point);

private:
  void setUpChart();

// private slots:
//   void updateChart();

// public slots:
//     void handleTimeout();

private:
  QBasicTimer timer;
  QString text;
  int step;
  qreal m_step;
  qreal m_x;
  qreal m_y;
};

#endif // FPCHART_H