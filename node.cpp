#include "node.h"

uint Node::idStatic = 0;
Node* Node::_selected = nullptr;
QMap<uint, Node*> Node::_map;

Node::Node(QGraphicsItem *parent): QGraphicsObject(parent),
    id(idStatic++)
{
    _map[id] = this;
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

Node::~Node()
{
    _map.remove(id);
}

Node *Node::selectedNode() { return _selected;}

void Node::setNodeSelected(bool toNotNull)
{
    if (_selected != (toNotNull ? this : nullptr)) {
        if (_selected) {
            _selected->setSelected(false);;
        }

        _selected = (toNotNull ? this : nullptr);
        emit selectNodeChanged();
        if (_selected) {
            _selected->setSelected(true);
        }
        // Перерисовать все вершины!
        foreach (Node* node, _map) {
            node->prepareGeometryChange();
        }
    }
}

void Node::deleteSelectedNode()
{
    if (_selected != nullptr) {
        Node *p = _selected;
        _selected->setNodeSelected(false);
        _map.remove(p->id);
        disconnect(p, 0, 0, 0);
        delete p;
    }
}

QRectF Node::boundingRect() const
{
    return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush((isSelected() ? Qt::cyan: Qt::white));
    painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);

    painter->drawText(-5, 4, QString::number(id));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    this->setPos(mapToScene(event->pos()));
//    QGraphicsObject::mouseMoveEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

