#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsEllipseItem>
#include "../abstractshape.h"
#include "edgerectangle.h"

class EllipseShape : public AbstractShape
{
    long _id;
    QGraphicsEllipseItem * self;
    EdgeRectangle * edge;
public:
    enum EllipseType {Type = AbstractType::Type + 3};
    explicit EllipseShape(const QPen &pen = QPen(), const QBrush & brush = QBrush(),
                     AbstractShape * parent = nullptr);
    virtual ~EllipseShape();
    int type() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
                       QWidget * widget);
    virtual void draw(qreal x1, qreal y1, qreal x2, qreal y2);

    virtual QGraphicsItem * currentEdge() const;
    void normalize(qreal x1, qreal y1, qreal width);

    virtual QString getName() const;
};

#endif // ELLIPSE_H
