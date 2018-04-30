#include "node.h"

uint Node::idStatic = 0;
Node* Node::_selected = nullptr;
QMap<uint, Node*> Node::_map;

Node::Node(QGraphicsItem *parent): QGraphicsObject(parent),
    id(idStatic++)
{
    _map[id] = this;
}

Node::~Node()
{
    _map.remove(id);
}

Node *Node::selectedNode() { return _selected;}

void Node::setNodeSelected(bool toNotNull)
{
    if (_selected != (toNotNull ? this : nullptr)) {
        _selected = (toNotNull ? this : nullptr);
        emit selectNodeChanged();
    }
    // Перерисовать все вершины!
    foreach (Node* node, _map) {
        node->prepareGeometryChange();
    }
}

void Node::deleteSelectedNode()
{
    if (_selected != nullptr) {
        Node *p = _selected;
        _selected->setNodeSelected(false);
        disconnect(p, 0, 0, 0);
        delete p;
    }
}

QRectF Node::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush((_selected == this? Qt::cyan: Qt::white));
    painter->drawEllipse(-30,-30,60,60);


    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setNodeSelected(false);
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    this->setPos(mapToScene(event->pos()));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (_selected != this)
        setNodeSelected();
    else
        setNodeSelected(false);

    Q_UNUSED(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
