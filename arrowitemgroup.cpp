#include "arrowitemgroup.h"

const qreal PI(3.14159265);

QPen ArrowItemGroup::_pen = QPen(Qt::black, 3, Qt::SolidLine);

ArrowItemGroup::ArrowItemGroup(QLineF lineF, QObject *parent)
    : QObject(parent), QGraphicsItemGroup()
{
    QLineF line;
    QLineF lL, lR; // /\ острая часть стрелы
    qreal x1, y1, x2, y2, angl, len = 20, r = 30;
    x1 = lineF.p1().x() + r * cos(lineF.angle() * PI / 180);
    y1 = lineF.p1().y() - r * sin(lineF.angle() * PI / 180);
    x2 = lineF.p2().x() - r * cos(lineF.angle() * PI / 180);
    y2 = lineF.p2().y() + r * sin(lineF.angle() * PI / 180);
    angl = lineF.angle();
    line.setLine(x1, y1, x2, y2);
    lL.setLine(x2, y2,
                x2 - len * cos((angl - 10) * PI / 180),
                y2 + len * sin((angl - 10) * PI / 180));
    lR.setLine(x2, y2,
                x2 - len * cos((angl + 10) * PI / 180),
                y2 + len * sin((angl + 10) * PI / 180));
    _line = new CustomLineItem(line, this);
    _lL = new CustomLineItem(lL, this);
    _lR = new CustomLineItem(lR, this);
    _line->setPen(_pen);
    _lL->setPen(_pen);
    _lR->setPen(_pen);
    addToGroup(_line);
    addToGroup(_lL);
    addToGroup(_lR);
//    setFlags(QGraphicsItem::ItemIsSelectable);
    createSelectionPolygon();
}

ArrowItemGroup::~ArrowItemGroup() { }

void ArrowItemGroup::createSelectionPolygon()
{
    QPolygonF nPolygon;
    qreal radAngle = _line->line().angle()* M_PI / 180;
    qreal dx = CustomLineItem::selectionOffset * sin(radAngle);
    qreal dy = CustomLineItem::selectionOffset * cos(radAngle);
    QPointF offset1 = QPointF(dx, dy);
    QPointF offset2 = QPointF(-dx, -dy);
    nPolygon << _line->line().p1() + offset1
             << _line->line().p1() + offset2
             << _line->line().p2() + offset2
             << _line->line().p2() + offset1;
    selectionPolygon = nPolygon;
    update();
}

void ArrowItemGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isSelected()) {
        setFlag(QGraphicsItem::ItemIsSelectable, false);
        setSelected(false);
    } else {
        setFlag(QGraphicsItem::ItemIsSelectable);
        setSelected(true);
    }
    Q_UNUSED(event);
}

QRectF ArrowItemGroup::boundingRect() const {
    return selectionPolygon.boundingRect();
}

QPainterPath ArrowItemGroup::shape() const{
    QPainterPath ret;
    ret.addPolygon(selectionPolygon);
    return ret;
}

void ArrowItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                           QWidget *widget){
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
//    painter->setPen(_line->pen());
//    painter->drawLine(_line->line());
//    if (isSelected()) {
//        painter->setPen(QPen(Qt::cyan, 6, Qt::SolidLine));
//        painter->drawLine(_line->line());
//    }
}
