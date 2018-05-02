#ifndef SCENE_H
#define SCENE_H

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
#include "node.h"
#include "arrowitemgroup.h"

class Scene : public QGraphicsScene
{
public:
    Scene(QObject *parent = Q_NULLPTR);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
