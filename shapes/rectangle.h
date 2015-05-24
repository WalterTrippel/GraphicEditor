#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsItem>
#include "../abstractshape.h"
#include "edgerectangle.h"


class Rectangle : public AbstractShape
{
    long _id;
    QGraphicsRectItem * self;
    EdgeRectangle * edge;
public:
    enum RectangleType {Type = AbstractType::Type + 2};
    explicit Rectangle(const QPen & pen = QPen(), const QBrush & brush = QBrush(),
                       AbstractShape * parent = nullptr);
    virtual ~Rectangle();
    int type() const;
    QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
                       QWidget * widget);
    virtual void draw(qreal x1, qreal y1, qreal x2, qreal y2);
    virtual QGraphicsItem * currentEdge() const;
    virtual void normalize(qreal x1, qreal y1, qreal width);

    virtual QString getName() const;
};

#endif // RECTANGLE_H
