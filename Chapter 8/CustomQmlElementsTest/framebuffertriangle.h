#ifndef FRAMEBUFFERTRIANGLE_H
#define FRAMEBUFFERTRIANGLE_H

#include <QQuickFramebufferObject>


class FrameBufferTriangle : public QQuickFramebufferObject
{
public:  
    explicit FrameBufferTriangle(QQuickItem* parent = nullptr);

    Renderer* createRenderer() const override;
};


#endif // FRAMEBUFFERTRIANGLE_H
