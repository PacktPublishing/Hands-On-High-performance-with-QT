#include "quickitemtriangle.h"

#include <QSGNode>
#include<QSGFlatColorMaterial>


QuickItemTriangle::QuickItemTriangle(QQuickItem* parent)
    : QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, true);
}


QSGNode* QuickItemTriangle::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* data)
{
    if (width() <= 0 || height() <= 0)
    {
        delete oldNode;
        return nullptr;
    }

    QSGGeometryNode* triangle = static_cast<QSGGeometryNode*>(oldNode);
    if (!triangle)
    {
        triangle = new QSGGeometryNode;
        triangle->setFlag(QSGNode::OwnsMaterial, true);
        triangle->setFlag(QSGNode::OwnsGeometry, true);
    }

    const QRectF rect = boundingRect();
    QSGGeometry* geometry = new	QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 3);

    QSGGeometry::Point2D* points = geometry->vertexDataAsPoint2D();

    points[0].x = rect.left();
    points[0].y = rect.top();
    points[1].x = rect.left() + rect.width() / 2.0;
    points[1].y = rect.bottom();
    points[2].x = rect.right();
    points[2].y = rect.top();

    triangle->setGeometry(geometry);

    QSGFlatColorMaterial* material = new QSGFlatColorMaterial;
    material->setColor(Qt::blue);
    triangle->setMaterial(material);

    return triangle;
}
