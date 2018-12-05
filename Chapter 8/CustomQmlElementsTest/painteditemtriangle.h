#ifndef PAINTEDITEMTRIANGLE_H
#define PAINTEDITEMTRIANGLE_H

#include <QQuickPaintedItem>

class PaintedItemTriangle : public	QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit PaintedItemTriangle(QQuickItem* parent = nullptr);
    void paint(QPainter* painter) override;
};

#endif // PAINTEDITEMTRIANGLE_H
