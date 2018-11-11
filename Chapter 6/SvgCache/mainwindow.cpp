#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>

#include "svgcache.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // find the test file
    QString path = "./";
    QString testfilePath = path + "svg filter red.svg";

    QFile fi(testfilePath);
    if(!fi.exists())
    {
        path = "../SvgCache/";
        testfilePath = path + "svg filter red.svg";
        fi.setFileName(testfilePath );
        if(!fi.exists())
        {
            QMessageBox::critical(this, "ERROR", "SVG files not found, looked in './' and '../SvgCache'");
        }
    }

    SvgCache cache;
    bool useChache = true;

    if(useChache)
    {
        ui->svgWidget->useCache(path + "svg filter red.svg", cache);
        ui->svgWidget_2->useCache(path + "svg filter red.svg", cache);
        ui->svgWidget_3->useCache(path + "svg filter red.svg", cache);
        ui->svgWidget_4->useCache(path + "svg filter red.svg", cache);

        ui->svgWidget_5->useCache(path + "pink rectangle.svg", cache);
        ui->svgWidget_6->useCache(path + "pink rectangle.svg", cache);
        ui->svgWidget_7->useCache(path + "pink rectangle.svg", cache);
        ui->svgWidget_8->useCache(path + "pink rectangle.svg", cache);

        ui->svgWidget_9->useCache(path + "ellipse and text.svg", cache);
        ui->svgWidget_10->useCache(path + "ellipse and text.svg", cache);
        ui->svgWidget_11->useCache(path + "ellipse and text.svg", cache);
        ui->svgWidget_12->useCache(path + "ellipse and text.svg", cache);
    }
    else
    {
        ui->svgWidget->load(path + "svg filter red.svg");
        ui->svgWidget_2->load(path + "svg filter red.svg");
        ui->svgWidget_3->load(path + "svg filter red.svg");
        ui->svgWidget_4->load(path + "svg filter red.svg");

        ui->svgWidget_5->load(path + "pink rectangle.svg");
        ui->svgWidget_6->load(path + "pink rectangle.svg");
        ui->svgWidget_7->load(path + "pink rectangle.svg");
        ui->svgWidget_8->load(path + "pink rectangle.svg");

        ui->svgWidget_9->load(path + "ellipse and text.svg");
        ui->svgWidget_10->load(path + "ellipse and text.svg");
        ui->svgWidget_11->load(path + "ellipse and text.svg");
        ui->svgWidget_12->load(path + "ellipse and text.svg");
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
