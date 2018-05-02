#include "scene.h"

Scene::Scene(QObject *parent): QGraphicsScene(parent)
{

}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::MouseButton::LeftButton && selectedItems().size() == 1) {
        // тут должны перерисовать стрелки!
    }
    QGraphicsScene::mouseMoveEvent(event);
}


