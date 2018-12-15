#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
//#include <QtGlobal> --> C++14
#include <QMetaEnum>


namespace {

    QString clientLineSeparator = "\n";
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    ui_->clientSendToolButton->setEnabled(false);
    ui_->clientConnectPushButton->setEnabled(false);
    ui_->clientDisconnectPushButton->setEnabled(false);

    connect(&client_, &QTcpSocket::connected, this, &MainWindow::connectionOpened);
    connect(&client_, &QTcpSocket::readyRead, this, &MainWindow::readServerResponse);

    connect(ui_->clientConnectPushButton, &QPushButton::clicked, this, &MainWindow::connectServer);
    connect(ui_->clientDisconnectPushButton, &QPushButton::clicked, this, &MainWindow::disconnectServer);
    connect(ui_->clientSendToolButton, &QToolButton::clicked, this, &MainWindow::sendMessageToServer);

    startServer();
}


MainWindow::~MainWindow()
{
    delete ui_;
}


void MainWindow::connectServer()
{
    ui_->clientConnectPushButton->setEnabled(false);

    client_.connectToHost(QHostAddress::LocalHost, server_.serverPort());
}


void MainWindow::disconnectServer()
{
    ui_->clientConnectPushButton->setEnabled(true);
    ui_->clientDisconnectPushButton->setEnabled(false);
    ui_->clientSendToolButton->setEnabled(false);

    client_.disconnectFromHost();
}


void MainWindow::acceptConnection()
{
    conn_ = server_.nextPendingConnection();

    connect(conn_, &QTcpSocket::readyRead, this, &MainWindow::readFromConnection);

    // c++14:
    //connect(&client_, qOverload<QAbstractSocket::SocketError>(&QTcpSocket::error), this,
    //        &MainWindow::displayClientError);
    connect(conn_, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),
            this, &MainWindow::displayServerError);

    ui_->serverOutputTextBrowser->insertPlainText(tr("New connection accepted.\n"));
}


void MainWindow::readFromConnection()
{
    auto bytes = conn_->readAll();

    if (bytes.endsWith(clientLineSeparator.toUtf8()))
    {
         ui_->serverOutputTextBrowser->insertPlainText(QString("received Client line: %1").arg(bytes.constData()));
    }
    else
    {
        // OPEN TODO:::
        // else: wait for more bytes till the line is full !!!

        ui_->serverOutputTextBrowser->insertPlainText(QString("ERROR: incomplete client line: %1 !!!").arg(bytes.constData()));
    }

    // echo!
    conn_->write(bytes.prepend("ECHO: "));
}


void MainWindow::connectionOpened()
{
    ui_->clientSendToolButton->setEnabled(true);
    ui_->clientConnectPushButton->setEnabled(false);
    ui_->clientDisconnectPushButton->setEnabled(true);

    QMessageBox::information(
                this, tr("TCP Client"),
                tr("Connected to %1, now you can send messages").arg(server_.serverPort()));
}


void MainWindow::sendMessageToServer()
{
    if (ui_->clientInputLineEdit->text().isEmpty())
    {
        return;
    }

    client_.write((ui_->clientInputLineEdit->text() + clientLineSeparator).toUtf8());
    ui_->clientInputLineEdit->clear();
}


void MainWindow::readServerResponse()
{
   auto bytes = client_.readAll();

   if (bytes.endsWith(clientLineSeparator.toUtf8()))
   {
       QMessageBox::information(
                   this, tr("TCP Client"),
                   tr("Server response: %1.").arg(bytes.constData()));
   }
   else
   {
       // OPEN TODO:::
       // else: wait for more bytes till the line is full !!!

       QMessageBox::information(
                   this, tr("TCP Client"),
                   tr("ERROR: incomplete server response: %1 !!!").arg(bytes.constData()));
   }
}


void MainWindow::displayClientError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err);

    QMessageBox::information(
                this, tr("TCP Client"),
                tr("Network error: %1.").arg(client_.errorString()));
}


void MainWindow::displayServerError(QAbstractSocket::SocketError err)
{
    if (err == QTcpSocket::RemoteHostClosedError)
    {
        ui_->serverOutputTextBrowser->insertPlainText(QString("Connection closed.\n"));
        return;
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();

    ui_->serverOutputTextBrowser->insertPlainText(QString("ERROR: ") + metaEnum.valueToKey(err) + "\n");
}


void MainWindow::startServer()
{
    connect(&server_, &QTcpServer::newConnection, this, &MainWindow::acceptConnection);

    // c++14:
    //connect(&client_, qOverload<QAbstractSocket::SocketError>(&QTcpSocket::error), this,
    //        &MainWindow::displayClientError);
    connect(&client_, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),
            this, &MainWindow::displayClientError);

    while (!server_.isListening() && !server_.listen())
    {
       auto ret = QMessageBox::critical(
                    this, tr("Server"),
                    tr("cannot start the server: %1.").arg(server_.errorString()),
                    QMessageBox::Retry | QMessageBox::Cancel);
       if (ret == QMessageBox::Cancel)
       {
           ui_->serverOutputTextBrowser->insertPlainText("ERROR: " + server_.errorString()  + "\n");
           return;
       }
    }

    ui_->clientConnectPushButton->setEnabled(true);
    ui_->serverOutputTextBrowser->insertPlainText(
                tr("Listening on port %1...\n").arg(server_.serverPort()));
}
