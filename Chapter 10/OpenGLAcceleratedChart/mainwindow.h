#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QChart>

#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addData(const std::vector<float>& x, const std::vector<float>& y, const QColor& color);
    void setChartTitle(const QString& title);

private:
    Ui::MainWindow *ui;
    QtCharts::QChart* chart_;
};

#endif // MAINWINDOW_H
