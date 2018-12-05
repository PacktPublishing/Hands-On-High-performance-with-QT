#ifndef TESTOPENGLWIDGET_H
#define TESTOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class TestOpenGLWidget
        : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    TestOpenGLWidget(QWidget* parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // TESTOPENGLWIDGET_H
