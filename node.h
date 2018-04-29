#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class Node : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Node(QGraphicsItem *parent = 0);
    const uint id;
    ~Node();
signals:

private:
    static uint idStatic;
    bool _selected;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public slots:

};

#endif // NODE_H
