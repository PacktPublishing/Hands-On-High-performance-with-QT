#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFutureWatcher>
#include <QImage>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButtonAll_clicked();
    void on_pushButtonSeparate_clicked();
    void onWatcherFinished();

private:
    void asynchFetchLabel(int index);
    bool checkTestFileFound();

    Ui::MainWindow *ui;    
    QVector<QLabel*> labels_;
    QString testfilePath_;

    QFuture<QPair<QImage, int>> future_;
    QFutureWatcher<QPair<QImage, int>> watcher_;
    QFutureWatcher<QVector<QImage>> listWatcher_;
};

#endif // MAINWINDOW_H
