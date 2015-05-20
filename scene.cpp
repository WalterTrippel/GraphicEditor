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
