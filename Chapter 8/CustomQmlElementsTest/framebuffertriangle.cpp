#include "framebuffertriangle.h"

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>


// TEST support - using OpenGL 1.1
//#define USE_OLD_OPENGL_API


class FrameBufferTriangleRenderer
        : public QQuickFramebufferObject::Renderer,
          protected QOpenGLFunctions
{
public:
    FrameBufferTriangleRenderer();

    void synchronize(QQuickFramebufferObject *item) override;
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    QQuickWindow* window_;
    QScopedPointer<QOpenGLShaderProgram> shader_;
    uint positionAttr_;
    uint colorAttr_;
    int matrixAttr_;
};


FrameBufferTriangle::FrameBufferTriangle(QQuickItem* parent)
    : QQuickFramebufferObject(parent)
{
}


auto FrameBufferTriangle::createRenderer() const -> Renderer*
{
    return new FrameBufferTriangleRenderer();
}


// impl. of a renderer

FrameBufferTriangleRenderer::FrameBufferTriangleRenderer()
    : shader_(new QOpenGLShaderProgram),
      positionAttr_((unsigned)-1),
      colorAttr_((unsigned)-1),
      matrixAttr_(-1)
{
    initializeOpenGLFunctions();

    //glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // opaque
    glClearColor(0.1f, 0.1f, 0.2f, 0.0f); // transparent

#ifndef USE_OLD_OPENGL_API
    // use OpenGl 2.0

    // just the default shaders:
    const char *vertexShaderSrc =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    const char *fragmentShaderSrc =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    shader_->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSrc);
    shader_->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSrc);
    shader_->link();
    positionAttr_ = shader_->attributeLocation("posAttr");
    colorAttr_ = shader_->attributeLocation("colAttr");
    matrixAttr_ = shader_->uniformLocation("matrix");
#endif
}


void FrameBufferTriangleRenderer::synchronize(QQuickFramebufferObject *item)
{
    window_ = item->window();

    FrameBufferTriangle* obj = static_cast<FrameBufferTriangle*>(item);
    Q_UNUSED(obj);

    // sync values ...
}


void FrameBufferTriangleRenderer::render()
{
#ifdef USE_OLD_OPENGL_API
    float relSize = 0.8f;

    // we use OpenGL 1.0 functions directly
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
#else
    // use OpenGl 2.0
    glClear(GL_COLOR_BUFFER_BIT);

    shader_->bind();

    QMatrix4x4 matrix;
    matrix.perspective(90.0f, 1.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -1);

    shader_->setUniformValue(matrixAttr_, matrix);

    float relSize = 0.8f;
    GLfloat vertices[] = {
        -relSize, -relSize, 0.0f,
        relSize, -relSize, 0.0f,
        0.0f, relSize, 0.0f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(positionAttr_, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(colorAttr_, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    shader_->release();
#endif
}


QOpenGLFramebufferObject* FrameBufferTriangleRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

