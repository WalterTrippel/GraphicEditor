#include "edgerectangle.h"

EdgeRectangle::EdgeRectangle(const QPen & pen, const QBrush & brush,
                             AbstractShape * parent) : AbstractShape(pen, brush, parent),
                                                       self(new QGraphicsRectItem)
{
}

EdgeRectangle::~EdgeRectangle()
{
    delete self;
    self = nullptr;
}

int EdgeRectangle::type() const
{
    return EdgeRectangleType::Type;
}

QGraphicsItem * EdgeRectangle::currentEdge() const
{
    return nullptr;
}

QRectF EdgeRectangle::boundingRect() const
{
    return self->boundingRect();
}

void EdgeRectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    self->paint(painter, option, widget);
}

void EdgeRectangle::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QPen localpen = QPen(Qt::red, 2, Qt::DashLine);
    self->setPen(localpen);
    self->setBrush(brush());
    self->setRect(x1, y1, x2 - x1, y2 - y1);
}

