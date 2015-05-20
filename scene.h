#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "abstractshape.h"

class Scene : public QGraphicsScene
{
    // Q_OBJECT

public:
    explicit Scene(QObject * parent = nullptr);
    virtual ~Scene();
    AbstractShape * currentShape();
};

#endif // SCENE_H
