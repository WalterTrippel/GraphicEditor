#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "abstractshape.h"
#include "shapes/edgerectangle.h"

class Scene : public QGraphicsScene
{
    // Q_OBJECT
    EdgeRectangle * commonEdge;
public:
    explicit Scene(QObject * parent = nullptr);
    virtual ~Scene();
    AbstractShape * currentShape();
    EdgeRectangle * currentEdge() const;
    EdgeRectangle * edge() const;
};

#endif // SCENE_H
