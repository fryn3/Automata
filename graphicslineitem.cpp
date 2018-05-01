#include "graphicslineitem.h"

GraphicsLineItem::GraphicsLineItem(QGraphicsItem *parent): QGraphicsLineItem(parent)
{
    setPen(QPen(Qt::black, 3, Qt::SolidLine));
}

GraphicsLineItem::GraphicsLineItem(const QLineF &line, QGraphicsItem *parent):
    QGraphicsLineItem(line, parent)
{
//    line.angle()
    setPen(QPen(Qt::black, 3, Qt::SolidLine));
}

void GraphicsLineItem::setLine(const QLineF &line)
{
    int r = 30;
    qreal x1, x2, y1, y2;
    x1 = line.p1().x() + r * cos(line.angle() * 3.14159265 / 180);
    y1 = line.p1().y() - r * sin(line.angle() * 3.14159265 / 180);
    x2 = line.p2().x() - r * cos(line.angle() * 3.14159265 / 180);
    y2 = line.p2().y() + r * sin(line.angle() * 3.14159265 / 180);
    QLineF *l = new QLineF(x1, y1, x2, y2);

    QGraphicsLineItem::setLine(*l);
}
