#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPushBtnClicked();

private:
    Ui::MainWindow *ui;

    // test support
    friend class WidgetClickTest;
};

#endif // MAINWINDOW_H
