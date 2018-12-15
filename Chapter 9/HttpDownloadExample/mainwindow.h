#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QFile>
#include <QNetworkReply>


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
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void updateDownloadProgress(qint64 readBytes, qint64 totalBytes);
    void enableDownloadBtn();
    void setHtttpProtocol();

private:
    void startRequest(const QUrl& url);
    QUrl getUrlToDownload() const;
    QString getTargetFileName() const;

    Ui::MainWindow *ui_;
    QProgressDialog progressDlg_;

    QFile file_;
    QUrl url_;
    QNetworkAccessManager netAccessMgr_;
    QNetworkReply* reply_ = nullptr;

    int httpGetId_ = -1;
    bool httpReqAborted_ = false;
};

#endif // MAINWINDOW_H
