#include "chartdisplay.h"
#include "chart.h"
#include <QDebug>

ChartDisplay::ChartDisplay(QWidget *parent) : QLabel(parent)
{
    chartDisplay = QImage();
}

ChartDisplay::~ChartDisplay()
{
}

void ChartDisplay::setChart(Chart *chart)
{
    this->chart = chart;
}

void ChartDisplay::drawChart()
{
    qDebug()<<"drawing";
    setPixmap(QPixmap::fromImage(chart->draw()));
}
