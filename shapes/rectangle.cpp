#include "rectangle.h"

Rectangle::Rectangle(const QPen & pen, const QBrush & brush,
                     AbstractShape * parent): AbstractShape(pen, brush, parent),
                                              self(new QGraphicsRectItem)
{
}

Rectangle::~Rectangle()
{
    delete self;
    self = nullptr;
}

int Rectangle::type() const
{
    return RectangleType::Type;
}

QRectF Rectangle::boundingRect() const
{
    return self->boundingRect();
}

void Rectangle::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    self->setPen(pen());
    self->setBrush(brush());

    self->setRect(x1, y1, x2 - x1, y2 - y1);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(self->boundingRect());
    self->paint(painter, option, widget);
}

