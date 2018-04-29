#include "node.h"

uint Node::idStatic = 0;

Node::Node(QGraphicsItem *parent) : QGraphicsObject(parent),
    _selected(false),
    id(idStatic++)
{
}

Node::~Node() { }

QRectF Node::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush((_selected? Qt::cyan: Qt::white));
    painter->drawEllipse(-30,-30,60,60);


    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    _selected = false;
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    this->setPos(mapToScene(event->pos()));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    _selected ^= 1;
    this->prepareGeometryChange();
    Q_UNUSED(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
