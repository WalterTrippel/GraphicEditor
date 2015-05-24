#include "edgerectangle.h"

EdgeRectangle::EdgeRectangle(const QPen & pen, const QBrush & brush,
                             AbstractShape * parent) : AbstractShape(pen, brush, parent),
                                                       self(new QGraphicsRectItem)
{
    _id = getId();
    name = getName();
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
    QRectF tmp = boundingRect();
    painter->setPen(Qt::black);
    painter->drawText(tmp, name);

    self->paint(painter, option, widget);
}

void EdgeRectangle::normalize(qreal x1, qreal y1, qreal width)
{
    draw(x1, y1, width, width);
}

void EdgeRectangle::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QPen localpen = QPen(Qt::red, 2, Qt::DashLine);
    self->setPen(localpen);
    self->setBrush(brush());
    self->setRect(x1, y1, x2 - x1, y2 - y1);
}

QString EdgeRectangle::getName() const
{
    //return QString("Edge_").append(std::to_string(_id).c_str());
    return "";
}

