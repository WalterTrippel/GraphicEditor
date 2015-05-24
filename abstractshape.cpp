#include "abstractshape.h"

AbstractShape::AbstractShape(const QPen &pen, const QBrush &brush, QGraphicsItem * parent) :
    QGraphicsItem(parent), _pen(pen), _brush(brush)
{
    static long _id = 0;
    id = _id++;
}

AbstractShape::~AbstractShape()
{
}

int AbstractShape::type() const
{
    return Type;
}

void AbstractShape::setBrush(const QBrush &brush)
{
    this->_brush = brush;
}

void AbstractShape::setPen(const QPen &pen)
{
    this->_pen = pen;
}

QPen AbstractShape::pen() const
{
    return _pen;
}

QBrush AbstractShape::brush() const
{
    return _brush;
}

long AbstractShape::getId() const
{
    return id;
}
