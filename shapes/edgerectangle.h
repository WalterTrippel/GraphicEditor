#ifndef EDGERECTANGLE_H
#define EDGERECTANGLE_H

#include <QGraphicsItem>
#include "../abstractshape.h"

class EdgeRectangle : public AbstractShape
{
    long _id;
    QGraphicsRectItem * self;
public:

    enum EdgeRectangleType {Type = AbstractType::Type + 3};
    explicit EdgeRectangle(const QPen & pen = QPen(), const QBrush & brush = QBrush(),
                           AbstractShape * parent = nullptr);
    virtual ~EdgeRectangle();
    int type() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
                       QWidget * widget);
    virtual void draw(qreal x1, qreal y1, qreal x2, qreal y2);
    virtual QGraphicsItem * currentEdge() const;
    void normalize(qreal x1, qreal y1, qreal width);

    virtual QString getName() const;
};

#endif // EDGERECTANGLE_H
