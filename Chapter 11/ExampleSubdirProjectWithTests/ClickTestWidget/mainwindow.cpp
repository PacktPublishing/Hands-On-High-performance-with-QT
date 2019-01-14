#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushBtnClicked()
{
    if(ui->lineEdit->text() == "Clicked!")
    {
        ui->lineEdit->setText("Un-clicked!");
    }
    else
    {
        ui->lineEdit->setText("Clicked!");
    }
}
