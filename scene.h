#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "abstractshape.h"
#include "shapes/edgerectangle.h"
#include "shapes/linesegment.h"

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

    QList<LineSegment *> lines;
    QList<AbstractShape *> shapes;
};

#endif // SCENE_H
