QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

INCLUDEPATH += ../ClickTestWidget

TEMPLATE = app

SOURCES +=  tst_widgetclicktest.cpp \
    ../ClickTestWidget/mainwindow.cpp

FORMS += \
    ../ClickTestWidget/mainwindow.ui

HEADERS += \
    ../ClickTestWidget/mainwindow.h
