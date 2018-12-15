#ifndef TESTOPENGLWIDGET_H
#define TESTOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>


/**
 * @brief
 *  Paints a sipmlest OpenGL triangle, uses oldskool v.1.0 API, for demonstration only!
 */
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
