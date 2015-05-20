#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <QGraphicsLineItem>
#include "../abstractshape.h"

class LineSegment : public AbstractShape
{
    QGraphicsLineItem * self;
public:
    enum LineSegmentType {Type = AbstractType::Type + 1};
    explicit LineSegment(const QPen &pen = QPen(), const QBrush & brush = QBrush(),
                         AbstractShape * parent = nullptr);
    virtual ~LineSegment();
    int type() const;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
                       QWidget * widget);
    virtual void draw(qreal x1, qreal y1, qreal x2, qreal y2);

};

#endif // LINESEGMENT_H
