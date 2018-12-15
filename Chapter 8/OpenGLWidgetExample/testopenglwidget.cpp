#include "testopenglwidget.h"


TestOpenGLWidget::TestOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void TestOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1,1,1,0); // white
}

void TestOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);

    // you could set the viewport and perspective
}

void TestOpenGLWidget::paintGL()
{
    float relSize = 0.8f;

    // we use OpenGL 1.0 functions for simplicity
    //  - set QT_OPENGL to desktop if it's not working
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 0.0, 0.0); // red
    glVertex3f(-relSize, -relSize, 0);
    glColor3f(0.0, 1.0, 0.0); // green
    glVertex3f(relSize, -relSize, 0);
    glColor3f(0.0, 0.0, 1.0); // blue
    glVertex3f(0.0, relSize, 0);

    glEnd();
}
