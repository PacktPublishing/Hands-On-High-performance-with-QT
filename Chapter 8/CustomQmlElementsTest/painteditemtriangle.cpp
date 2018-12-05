#include "painteditemtriangle.h"

#include <QPolygonF>
#include <QPainter>


PaintedItemTriangle::PaintedItemTriangle(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
}


void PaintedItemTriangle::paint(QPainter* painter)
{
    const auto& rect = contentsBoundingRect();

    const QPolygonF polygon({
                {0,	0},
                {rect.width(), 0},
                {0.5 * rect.width(), rect.height()},
                {0,	0}});

    QBrush brush(Qt::yellow);
    painter->setBrush(brush);

    painter->drawPolygon(polygon);
}
