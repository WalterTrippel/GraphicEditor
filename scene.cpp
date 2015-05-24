#include "scene.h"
#include "shapes/linesegment.h"
#include <QDebug>

Scene::Scene(QObject * parent) : QGraphicsScene(parent),
                                 commonEdge(new EdgeRectangle)
{
    addItem(commonEdge);
}

Scene::~Scene()
{
    delete commonEdge;
    commonEdge = nullptr;
}

EdgeRectangle * Scene::edge() const
{
    return commonEdge;
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
