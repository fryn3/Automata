#ifndef ARROW_H
#define ARROW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGraphicsView>
#include <QPushButton>
#include <QVector>
#include <QMap>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QGraphicsItemGroup>
#include <QPen>
#include <QPainter>
#include "cmath"
#include "node.h"
#include "customlineitem.h"

extern const qreal PI;

class ArrowItemGroup: public QObject, public QGraphicsItemGroup {
    Q_OBJECT
public:
    ArrowItemGroup(QLineF lineF, QObject *parent = nullptr);
    virtual ~ArrowItemGroup();
private:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option,
                QWidget* widget = 0);
    static QPen _pen;
    QPolygonF selectionPolygon;
    CustomLineItem *_line, *_lL, *_lR;
    void createSelectionPolygon();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};


#endif // ARROW_H
