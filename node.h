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
    ~Node();
    const uint id;
    static Node *selectedNode();
    static void deleteSelectedNode();
    void setNodeSelected(bool toNotNull = true);
    enum {
        radius = 30
    };
//    const static uint radius;
public slots:

signals:
    void selectNodeChanged();
private:
    static uint idStatic;
    static Node* _selected;
    static QMap<uint, Node*> _map;

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NODE_H
