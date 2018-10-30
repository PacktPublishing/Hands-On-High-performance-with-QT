#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagereader.h"

#include <QVector>
#include <QMessageBox>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labels_ = {
        ui->label, ui->label_2, ui->label_3, ui->label_4, ui->label_5, ui->label_6,
        ui->label_7, ui->label_8, ui->label_9, ui->label_10
    };

    // find the test file
    testfilePath_ = "./qt-logo.png";

    QFile fi(testfilePath_);
    if(!fi.exists())
    {
        testfilePath_ = "../ConcurrentAndFutures/qt-logo.png";
        fi.setFileName(testfilePath_);
        if(!fi.exists())
        {
            testfilePath_.clear();
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAll_clicked()
{
    if (!checkTestFileFound())
    {
        return;
    }

    ImageReader reader;
    QStringList fileNames;

    for(auto& label : labels_)
    {
        label->setPixmap(QPixmap());
        label->setText("loading...");

        // using one file for simplicity
        fileNames << testfilePath_;
    }

    Q_ASSERT(labels_.size() > 0);

    auto future = reader.read(fileNames);

    QObject::connect(&listWatcher_, &QFutureWatcher<QVector<QImage>>::finished, this,
             [=]() {
                auto count = future.result().size();
                Q_ASSERT(count <= labels_.count());
                qDebug() << " -- fetched set of" << count << "images";
                int index = 0;
                for(auto& image : future.result())
                {
                     labels_[index]->setPixmap(QPixmap::fromImage(image));
                     ++index;
                }
             });

    listWatcher_.setFuture(future);
}


void MainWindow::on_pushButtonSeparate_clicked()
{
    if (!checkTestFileFound())
    {
        return;
    }

    for(auto& label : labels_)
    {
        label->setPixmap(QPixmap());
        label->setText("loading...");
    }

    Q_ASSERT(labels_.size() > 0);
    asynchFetchLabel(0);
}


void MainWindow::onWatcherFinished()
{
    qDebug() << " -- fetched img. index=" << future_.result().second;

    auto& label = labels_[future_.result().second];
    label->setPixmap(QPixmap::fromImage(future_.result().first));
    disconnect(&watcher_, &QFutureWatcher<QImage>::finished, this, &MainWindow::onWatcherFinished);

    if(future_.result().second < labels_.size() - 1)
    {
        asynchFetchLabel(future_.result().second + 1);
    }
}


void MainWindow::asynchFetchLabel(int index)
{
    ImageReader reader;
    // using one file for simplicity
    future_ = reader.read(testfilePath_, index);

    connect(&watcher_, &QFutureWatcher<QImage>::finished, this, &MainWindow::onWatcherFinished);
    watcher_.setFuture(future_);
}


bool MainWindow::checkTestFileFound()
{
    if (testfilePath_.isEmpty())
    {
        QMessageBox::critical(
            this, "Error",
            "Testfile not found! Please copy 'qt-logo.png' to the start directory!");
        return false;
    }

    return true;
}
