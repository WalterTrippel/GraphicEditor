#include "linesegment.h"

LineSegment::LineSegment(const QPen &pen, const QBrush &brush,
                         AbstractShape *parent) : AbstractShape(pen, brush, parent),
                                                  self(new QGraphicsLineItem),
                                                  edge(new EdgeRectangle)
{
    _id = getId();
    name = getName();
}

LineSegment::~LineSegment()
{
    delete self;
    self = nullptr;

    delete edge;
    edge = nullptr;
}

int LineSegment::type() const
{
    return LineSegmentType::Type;
}

QRectF LineSegment::boundingRect() const
{
    return self->boundingRect();
}

void LineSegment::normalize(qreal x1, qreal y1, qreal width)
{
}

QGraphicsItem * LineSegment::currentEdge() const
{
    return this->edge;
}

void LineSegment::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    self->setPen(pen());
    self->setLine(x1, y1, x2, y2);
}

void LineSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    QRectF tmp = boundingRect();
    painter->setPen(Qt::black);
    painter->drawText(tmp.center().x(), tmp.center().y(), name);

    self->paint(painter, option, widget);
}

QString LineSegment::getName() const
{
    return QString("Line_").append(std::to_string(_id).c_str());
}
