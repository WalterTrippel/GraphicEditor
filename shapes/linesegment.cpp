#include "linesegment.h"

LineSegment::LineSegment(const QPen &pen, const QBrush &brush,
                         AbstractShape *parent) : AbstractShape(pen, brush, parent),
                                                  self(new QGraphicsLineItem)
{
}

LineSegment::~LineSegment()
{
    delete self;
    self = nullptr;
}

int LineSegment::type() const
{
    return LineSegmentType::Type;
}

QRectF LineSegment::boundingRect() const
{
    return self->boundingRect();
}

void LineSegment::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    self->setPen(pen());
    self->setLine(x1, y1, x2, y2);

}

void LineSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    painter->drawRect(self->boundingRect());
    self->paint(painter, option, widget);
}
