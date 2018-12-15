#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>


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
    void connectServer();
    void disconnectServer();
    void connectionOpened();
    void acceptConnection();
    void readFromConnection();
    void sendMessageToServer();
    void readServerResponse();
    void displayClientError(QAbstractSocket::SocketError err);
    void displayServerError(QAbstractSocket::SocketError err);

private:
    void startServer();

    Ui::MainWindow* ui_;
    QTcpServer server_;
    QTcpSocket client_;
    QTcpSocket* conn_;
};

#endif // MAINWINDOW_H
