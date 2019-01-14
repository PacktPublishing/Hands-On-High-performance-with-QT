#include <QtTest>
#include <QCoreApplication>

#include "mainwindow.h"
#include "ui_mainwindow.h"


class WidgetClickTest : public QObject
{
    Q_OBJECT

public:
    WidgetClickTest();
    ~WidgetClickTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void clickTest();
    void keyboardTest();
    void benchmarkTest();

    void dataDrivenTest_data();
    void dataDrivenTest();

private:
    MainWindow* mainWnd_ = nullptr;
};


WidgetClickTest::WidgetClickTest()
{
    mainWnd_ = new MainWindow();
    mainWnd_->show();
}

WidgetClickTest::~WidgetClickTest()
{
    delete mainWnd_;
    mainWnd_ = nullptr;
}

void WidgetClickTest::initTestCase()
{

}

void WidgetClickTest::cleanupTestCase()
{

}

void WidgetClickTest::clickTest()
{
    auto tstLineEdit = mainWnd_->ui->lineEdit;
    auto tstPushBtn = mainWnd_->ui->pushButton;

    // initial:
    QCOMPARE(tstLineEdit->text(), QString("waiting..."));

    // after click
    QTest::mouseClick(tstPushBtn, Qt::LeftButton);
    QCOMPARE(tstLineEdit->text(), QString("Clicked!"));

    // after 2nd click
    QTest::mouseClick(tstPushBtn, Qt::LeftButton);
    QCOMPARE(tstLineEdit->text(), QString("Un-clicked!"));

    // signal
    QSignalSpy spy(tstPushBtn, SIGNAL(clicked()));

    QTest::mouseClick(tstPushBtn, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void WidgetClickTest::keyboardTest()
{
    auto tstLineEdit = mainWnd_->ui->lineEdit;
    auto tstPushBtn = mainWnd_->ui->pushButton;

    // input
    QTest::keyClicks(tstLineEdit, "a", Qt::ControlModifier);
    QTest::keyClick(tstLineEdit, Qt::Key_Delete);
    QVERIFY(tstLineEdit->text().isEmpty());

    QTest::keyClicks(tstLineEdit, "hello world");
    QCOMPARE(tstLineEdit->text(), QString("hello world"));

    // after click
    QTest::mouseClick(tstPushBtn, Qt::LeftButton);
    QCOMPARE(tstLineEdit->text(), QString("Clicked!"));
}

void WidgetClickTest::benchmarkTest()
{
    auto tstLineEdit = mainWnd_->ui->lineEdit;
    QString longString = "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"
            "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"
            "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"
            "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"
            "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"
            "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss";

    QBENCHMARK {
        QTest::keyClicks(tstLineEdit, longString);
    }
}

void WidgetClickTest::dataDrivenTest_data()
{
    QTest::addColumn<QString>("inputColumn");
    QTest::addColumn<QString>("resultColumn");

    QTest::newRow("lower case") << "elysium" << "elysium";
    QTest::newRow("mixed case") << "Elysium" << "elysium";
    QTest::newRow("camel case") << "ElySium" << "elysium";
    QTest::newRow("upper case") << "ELYSIUM" << "elysium";
    QTest::newRow("error case") << "ELYSIUM1" << "elysium";
}

void WidgetClickTest::dataDrivenTest()
{
    QFETCH(QString, inputColumn);
    QFETCH(QString, resultColumn);
    QCOMPARE(inputColumn.toLower(), resultColumn);
}


QTEST_MAIN(WidgetClickTest)

#include "tst_widgetclicktest.moc"
