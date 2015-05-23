#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QGraphicsItem>
#include "../abstractshape.h"
#include "edgerectangle.h"

class Triangle : public AbstractShape
{
    QGraphicsPolygonItem * self;
    EdgeRectangle * edge;
public:
    enum TriangleType {Type = AbstractType::Type + 4};
    explicit Triangle(const QPen & pen = QPen(), const QBrush & brush = QBrush(),
                      AbstractShape * parent = nullptr);
    virtual ~Triangle();
    int type() const;
    QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
                       QWidget * widget);
    virtual void draw(qreal x1, qreal y1, qreal x2, qreal y2);
    virtual QGraphicsItem * currentEdge() const;
    virtual void normalize(qreal x1, qreal y1, qreal width);
};

#endif // TRIANGLE_H
