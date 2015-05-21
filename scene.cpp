#include "scene.h"
#include "shapes/linesegment.h"
#include <QDebug>

Scene::Scene(QObject * parent) : QGraphicsScene(parent)
{
}

Scene::~Scene()
{
}

AbstractShape * Scene::currentShape()
{
    return (AbstractShape *)items().first();
}

EdgeRectangle * Scene::currentEdge() const
{
    EdgeRectangle * tmp = (EdgeRectangle *)items().at(1);
    return tmp;
}
