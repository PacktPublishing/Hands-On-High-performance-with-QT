#include "framebuffertriangle.h"


#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QOpenGLFunctions>

#include <QAbstractOpenGLFunctions>



class FrameBufferTriangleRenderer : public QQuickFramebufferObject::Renderer
{
public:
    FrameBufferTriangleRenderer();

    void synchronize(QQuickFramebufferObject *item) override;
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    QQuickWindow* window_;
    QScopedPointer<QOpenGLVertexArrayObject> vao_;
    QScopedPointer<QOpenGLBuffer> vertexArray_;


};



FrameBufferTriangle::FrameBufferTriangle(QQuickItem* parent)
{

}

auto FrameBufferTriangle::createRenderer() const -> Renderer*
{

}


FrameBufferTriangleRenderer::FrameBufferTriangleRenderer()
{
//    // Create a colored triangle
//    static const QVector3D triVertexes[] =
//    {
//      QVector3D( 0.00f,  0.75f, 1.0f),
//      QVector3D( 0.75f, -0.75f, 1.0f),
//      QVector3D(-0.75f, -0.75f, 1.0f)
//    };
//    static const QVector3D triVertexColors[] =
//    {
//      QVector3D(1.0f, 0.0f, 0.0f),
//      QVector3D(0.0f, 1.0f, 0.0f),
//      QVector3D(0.0f, 0.0f, 1.0f)
//    };



//    if (!vao_->create())
//    {
//        qFatal("Unable to create VAO");
//    }

//    vao_->bind();



//    vao_->release();
}


// impl. of a renderer

void FrameBufferTriangleRenderer::synchronize(QQuickFramebufferObject *item)
{
    window_ = item->window();

    FrameBufferTriangle* obj = static_cast<FrameBufferTriangle*>(item);
    Q_UNUSED(obj);
}


void FrameBufferTriangleRenderer::render()
{
    //QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

    QOpenGLFunctions_1_0* f = context->versionFunctions<QOpenGLFunctions_1_0>();

    float relSize = 0.8f;

    // we use OpenGL functions directly
    //  - set QT_OPENGL to desktop if it's not working
    f->glClearColor(1,1,1,0); // white

    f->glCQOpenGLFunctionslear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    f->glBegin(GL_TRIANGLES);

    f->glColor3f(1.0, 0.0, 0.0); // red
    f->glVertex3f(-relSize, -relSize, 0);
    f->glColor3f(0.0, 1.0, 0.0); // green
    f->glVertex3f(relSize, -relSize, 0);
    f->glColor3f(0.0, 0.0, 1.0); // blue
    f->glVertex3f(0.0, relSize, 0);

    f->glEnd();

    //    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



//    m_render.render();

//    vao_->bind();
//    functions->glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, Q_NULLPTR);
//    vao_->release();

//    window_->resetOpenGLState();
}


QOpenGLFramebufferObject* FrameBufferTriangleRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

