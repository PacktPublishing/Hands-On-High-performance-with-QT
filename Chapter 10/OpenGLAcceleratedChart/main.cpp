#include "mainwindow.h"
#include <QApplication>


void fillSinCosPlotData(std::vector<float>& x, std::vector<float>& y, unsigned points, bool cosinus = false)
{
    x.clear();
    y.clear();
    x.reserve(points);
    y.reserve(points);

    float tick = 2 * 3.14f / points; // PI=3.14xxx, but its only a test :-/

    for(unsigned i = 0; i < points; ++i)
    {
        x.push_back(tick * i);
        y.push_back(cosinus ? std::cos(tick * i) : std::sin(tick * i));
    }

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    MainWindow w;

    std::vector<float> x;
    std::vector<float> y;
    unsigned pointCount = 100000;

    fillSinCosPlotData(x, y, pointCount);
    w.addData(x, y, Qt::red);

    fillSinCosPlotData(x, y, pointCount, true);
    w.addData(x, y, Qt::green);
    w.setChartTitle(QString("OpenGL accelerated sinus & cosinus plot using %1 points each")
                        .arg(pointCount));

    w.show();

    return a.exec();
}
