#ifndef GRAPHICSLINEITEM_H
#define GRAPHICSLINEITEM_H

#include <QGraphicsLineItem>
#include <QPen>
#include <cmath>

class GraphicsLineItem : public QGraphicsLineItem
{
public:
    explicit GraphicsLineItem(QGraphicsItem * parent = nullptr);
    explicit GraphicsLineItem(const QLineF &line, QGraphicsItem *parent = nullptr);
    void setLine(const QLineF &line);
};

#endif // GRAPHICSLINEITEM_H
