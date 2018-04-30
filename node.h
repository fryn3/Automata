#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMap>

class Node : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Node(QGraphicsItem *parent = 0);
    const uint id;
    ~Node();
    static const Node* selectedNode();
    static void deleteSelectedNode();
public slots:

signals:
    void selectNodeChanged();
private:
    static uint idStatic;
    static Node* _selected;
    static QMap<uint, Node*> _map;
    void setNodeSelected(Node * n);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // NODE_H
