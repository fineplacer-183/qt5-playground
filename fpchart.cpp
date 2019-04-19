#include "fpchart.h"
#include <QTime>

FpChart::FpChart(QChartView *parent)
{
  ui = parent;
  setUpChart();
  // chartTimer = new QTimer(this);
  // connect(chartTimer, SIGNAL(timeout()), this, SLOT(updateChart()));
  // chartTimer->start(1000);
}

FpChart::~FpChart()
{
  delete axisX;
  delete axisY;
  delete hotAirChart;
  delete hotAirData;
}

void FpChart::setUpChart()
{
  using namespace QtCharts;

  hotAirData = new QLineSeries();
  
  // To present the data on the chart we need a QChart instance. We add the series to it, create the default axes, and set the title of the chart.
  hotAirChart = new QChart();
  hotAirChart->legend()->hide();
  hotAirChart->addSeries(hotAirData);
  hotAirData->append(0,0);

  // set pen for Series of dataSeriea
  QPen pen(QRgb(0xfdb157));
  pen.setWidth(5);
  hotAirData->setPen(pen);

  // customize chart title
   QFont font;
  font.setPixelSize(18);
  hotAirChart->setTitleFont(font);
  hotAirChart->setTitleBrush(QBrush(Qt::white));
  hotAirChart->setTitle("Customchart example");

  // Customize chart background
  QLinearGradient backgroundGradient;
  backgroundGradient.setStart(QPointF(0, 0));
  backgroundGradient.setFinalStop(QPointF(0, 1));
  backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
  backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
  backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
  hotAirChart->setBackgroundBrush(backgroundGradient);

  // Customize plot area background
  QLinearGradient plotAreaGradient;
  plotAreaGradient.setStart(QPointF(0, 1));
  plotAreaGradient.setFinalStop(QPointF(1, 0));
  plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
  plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
  plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
  hotAirChart->setPlotAreaBackgroundBrush(plotAreaGradient);
  hotAirChart->setPlotAreaBackgroundVisible(true);

  // Then we customize the axes.
  axisX = new QCategoryAxis();
  axisY = new QCategoryAxis();
  // Customize axis label font
  QFont labelsFont;
  labelsFont.setPixelSize(12);
  axisX->setLabelsFont(labelsFont);
  axisY->setLabelsFont(labelsFont);

  // Customize axis colors
  QPen axisPen(QRgb(0xd18952));
  axisPen.setWidth(2);
  axisX->setLinePen(axisPen);
  axisY->setLinePen(axisPen);

  // Customize axis label colors
  QBrush axisBrush(Qt::white);
  axisX->setLabelsBrush(axisBrush);
  axisY->setLabelsBrush(axisBrush);

  // Customize grid lines and shades
  axisX->setGridLineVisible(true);
  axisY->setGridLineVisible(true);
  axisY->setShadesPen(Qt::NoPen);
  axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
  axisY->setShadesVisible(true);  
  
  // Then the axis label values and ranges. 
  // Once the axes are ready, we set them to be used by the chart.
  // axisX->append("low", 10);
  // axisX->append("optimal", 20);
  // axisX->append("high", 30);
  axisX->setRange(0, 30);
  axisX->setTickInterval(5);
  axisX->setTickType(QValueAxis::TickType::TicksDynamic);
  

  // axisY->append("slow", 10);
  // axisY->append("med", 20);
  // axisY->append("fast", 30);
  axisY->append("-10", -10);
  axisY->append("-5", -5);
  axisY->append("0", 0);
  axisY->append("5", 5);
  axisY->append("10", 10);
  axisX->setTickInterval(5);
  axisY->setRange(-10, 10);

  hotAirChart->addAxis(axisX, Qt::AlignBottom);
  hotAirChart->addAxis(axisY, Qt::AlignLeft);
  hotAirData->attachAxis(axisX);
  hotAirData->attachAxis(axisY);
  
  
  ui->setRenderHint(QPainter::Antialiasing);
  ui->setChart(hotAirChart);

  qsrand((uint) QTime::currentTime().msec());

  QObject::connect(&chartTimer, &QTimer::timeout, this, &FpChart::handleTimeout);
  chartTimer.setInterval(1000);
  
  chartTimer.start();
}

void FpChart::addDataPoint(QPointF dataPoint)
{
  hotAirData->append(dataPoint);
  qInfo() << __PRETTY_FUNCTION__  << " added Point: " << dataPoint <<
    " len now: " << hotAirData->count();
  // updateChart();
}

void FpChart::updateChart()
{
  // hotAirChart->scroll(0, 0);
  // ui->repaint();
}

void FpChart::handleTimeout()
{
    // qreal x = hotAirChart->plotArea().width() / xAxis->tickCount();
    qreal y = (axisX->max() - axisX->min()) / axisX->tickCount();
    m_x += y;
    m_y = qrand() % 5 - 2.5;
    // hotAirData->append(m_x, m_y);
    // hotAirChart->scroll(x, 0);
    hotAirChart->update();
    
    if (m_x == 100)
        chartTimer.stop();
}