#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChartView>
#include <QLineSeries>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart_ = new QtCharts::QChart;
    chart_->legend()->hide();

    auto chartView = new QtCharts::QChartView(chart_);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
    resize(600, 400);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addData(
        const std::vector<float>& x,
        const std::vector<float>& y,
        const QColor& color)
{
    Q_ASSERT(x.size() == y.size());

    auto curve = new QtCharts::QLineSeries;
    curve->setUseOpenGL(true); // accelerate!

    QPen pen = curve->pen();
    pen.setColor(color);
    pen.setWidthF(0.1);
    curve->setPen(pen);

    QList<QPointF> points;

    for(size_t i = 0; i < x.size(); ++i)
    {
        QPointF p(x[i], y[i]);
        points << p;
    }

    curve->append(points);

    chart_->addSeries(curve);
    chart_->createDefaultAxes();
}


void MainWindow::setChartTitle(const QString& title)
{
    Q_ASSERT(chart_);
    chart_->setTitle(title);
}
