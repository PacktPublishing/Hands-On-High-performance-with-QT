#ifndef QUICKITEMTRIANGLE_H
#define QUICKITEMTRIANGLE_H

#include <QQuickItem>


class QuickItemTriangle : public QQuickItem
{
    Q_OBJECT
public:
    QuickItemTriangle(QQuickItem* parent = nullptr);

protected:
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* data) override;

};

#endif // QUICKITEMTRIANGLE_H
