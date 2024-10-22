#pragma once
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "TrenchCoat.h"

#define QT_CHARTS_USE_NAMESPACE

class CoatChartWidget : public QWidget {
    Q_OBJECT

public:
    CoatChartWidget(const std::vector<Coat>& coats, QWidget* parent = nullptr);

private:
    void createBarChart(const std::vector<Coat>& coats);
};
