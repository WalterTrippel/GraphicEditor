#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsEllipseItem>
#include "../abstractshape.h"
#include "edgerectangle.h"

class Ellipse : public AbstractShape
{
    QGraphicsEllipseItem * self;
    EdgeRectangle * edge;
public:
    enum EllipseType {Type = AbstractType::Type + 3};
    explicit Ellipse(const QPen &pen = QPen(), const QBrush & brush = QBrush(),
                     AbstractShape * parent = nullptr);
    virtual ~Ellipse();
    int type() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
                       QWidget * widget);
    virtual void draw(qreal x1, qreal y1, qreal x2, qreal y2);

    virtual QGraphicsItem * currentEdge() const;
    void normalize(qreal x1, qreal y1, qreal width);
};

#endif // ELLIPSE_H
