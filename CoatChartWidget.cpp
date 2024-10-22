#include "CoatChartWidget.h"
#include "TrenchCoat.h"
#include <vector>
#include <QVBoxLayout>

CoatChartWidget::CoatChartWidget(const std::vector<Coat>& coats, QWidget* parent) // constructor
    : QWidget(parent) {
    createBarChart(coats);
}

void CoatChartWidget::createBarChart(const std::vector<Coat>& coats) { // function to create the bar chart
    QBarSet* barSet = new QBarSet("Coats");

    //Counting the number of coats per size
    std::map<int, int> sizeCount; // key = size, value = number of coats with that size
    for (const Coat& coat : coats) {
        for(int i=0;i<coat.getQuantity();i++)
            sizeCount[coat.getSize()]++;
    }

    for (const auto& pair : sizeCount) { // for each pair in sizeCount
        *barSet << pair.second; // add the number of coats to the barSet
    }

    QBarSeries* series = new QBarSeries(); // create a new bar series
    series->append(barSet); // append the barSet to the series

    QChart* chart = new QChart(); // create a new chart
    chart->addSeries(series);
    chart->setTitle("Number of Coats per Size");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories; // list of categories
    for (const auto& pair : sizeCount) { // for each pair in sizeCount
        categories << QString::number(pair.first); // add the size to the categories
    }

    QBarCategoryAxis* axisX = new QBarCategoryAxis(); // create a new bar category axis
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Find the maximum value in the sizeCount map for the Y axis range to use it in the chart ( to set the maximum value of the Y axis to the maximum value in the sizeCount map)
    auto maxElement = std::max_element(sizeCount.begin(), sizeCount.end(), 
        [](const auto& a, const auto& b) { return a.second < b.second; }); 
    int maxValue = (maxElement != sizeCount.end()) ? maxElement->second : 0;

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, maxValue);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}
