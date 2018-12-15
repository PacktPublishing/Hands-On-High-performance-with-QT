#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QDir>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    progressDlg_.setWindowTitle(tr("HTTP Progress"));
    progressDlg_.close();
    ui_->urlLineEdit->setText("www.qt.com");

    connect(ui_->urlLineEdit, &QLineEdit::textChanged, this, &MainWindow::enableDownloadBtn);
    connect(ui_->downloadPushButton, &QPushButton::clicked, this, &MainWindow::downloadFile);
    connect(ui_->sslCheckBox, &QCheckBox::clicked, this, &MainWindow::setHtttpProtocol);
    connect(&progressDlg_, &QProgressDialog::canceled, this, &MainWindow::cancelDownload);
}


MainWindow::~MainWindow()
{
    delete ui_;
}


// slots

void MainWindow::downloadFile()
{
    url_= getUrlToDownload();
    auto fname = getTargetFileName();

    if (QFile::exists(fname))
    {
        if (QMessageBox::question(
                    this, tr("HTTP"),
                    tr("File %1 already exists in the current directory. Overwrite?")
                    .arg(fname),
                    QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
        {
            return;
        }
        QFile::remove(fname);
    }

    file_.setFileName(fname);
    if (!file_.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(
                    this, tr("HTTP"),
                    tr("File save failed %1: %2.")
                        .arg(fname).arg(file_.errorString()));
        file_.setFileName("");
        return;
    }

    progressDlg_.setLabelText(tr("Downloading %1 ...").arg(fname));
    progressDlg_.show();
    ui_->downloadPushButton->setEnabled(false);

    // download
    startRequest(url_);
}


void MainWindow::cancelDownload()
{
    if(!reply_)
    {
        return;
    }

    ui_->infoLabel->setText(tr("Download canceled."));
    httpReqAborted_ = true;
    reply_->abort();
    ui_->downloadPushButton->setEnabled(true);
}


void MainWindow::httpFinished()
{
    if (httpReqAborted_)
    {
        if (file_.isOpen())
        {
            file_.close();
            file_.remove();
        }
        reply_->deleteLater();
        reply_ = nullptr;
        progressDlg_.close();
        return;
    }

    progressDlg_.close();
    file_.flush();
    file_.close();

    QVariant redirectTarget = reply_->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply_->error())
    {
        file_.remove();
        QMessageBox::information(
                    this, tr("HTTP"),
                    tr("Download failed: %1.").arg(reply_->errorString()));
        ui_->infoLabel->setText(tr("Type URL to download"));
        ui_->downloadPushButton->setEnabled(true);
    }
    else if (!redirectTarget.isNull())
    {
        QUrl newUrl = url_.resolved(redirectTarget.toUrl());
        if (QMessageBox::question(
                    this, tr("HTTP"),
                    tr("Redirect to %1 ?").arg(newUrl.toString()),
                    QMessageBox::Yes | QMessageBox::No)
           == QMessageBox::Yes)
        {
            url_ = newUrl;
            reply_->deleteLater();
            reply_ = nullptr;
            file_.open(QIODevice::WriteOnly);
            file_.resize(0);
            startRequest(url_);
            return;
        }
    }
    else
    {
        ui_->infoLabel->setText(tr("Downloaded \"%1\" to \"%2.\"")
                                    .arg(getTargetFileName()).arg(QDir::currentPath()));
        ui_->downloadPushButton->setEnabled(true);
    }

    reply_->deleteLater();
    reply_ = nullptr;
}


void MainWindow::httpReadyRead()
{
    // we could also read it all at once at the finished() signal of the QNetworkReply!

    if (file_.isOpen())
    {
        file_.write(reply_->readAll());
    }
}


void MainWindow::updateDownloadProgress(qint64 readBytes, qint64 totalBytes)
{
    if (httpReqAborted_)
    {
        return;
    }

    progressDlg_.setMaximum(totalBytes);
    progressDlg_.setValue(readBytes);
}


void MainWindow::enableDownloadBtn()
{
    bool enable = !ui_->urlLineEdit->text().isEmpty();
    ui_->downloadPushButton->setEnabled(enable);
}


void MainWindow::setHtttpProtocol()
{
    ui_->urlTextLabel->setText(
        ui_->sslCheckBox->isChecked() ? "https://" : "http://"
    );
}


// private

void MainWindow::startRequest(const QUrl& url)
{
    httpReqAborted_ = false;
    reply_ = netAccessMgr_.get(QNetworkRequest(url));

    connect(reply_, &QNetworkReply::finished, this, &MainWindow::httpFinished);
    connect(reply_, &QNetworkReply::readyRead, this, &MainWindow::httpReadyRead);
    connect(reply_, &QNetworkReply::downloadProgress, this, &MainWindow::updateDownloadProgress);
}


QUrl MainWindow::getUrlToDownload() const
{
    return
        ui_->urlTextLabel->text() +  ui_->urlLineEdit->text();
}


QString MainWindow::getTargetFileName() const
{
    QFileInfo fi(getUrlToDownload().path());
    QString fname = fi.fileName();

    if (fname.isEmpty())
    {
        fname = "index.html";
    }

    return fname;
}
