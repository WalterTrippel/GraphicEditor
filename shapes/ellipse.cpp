#include "ellipse.h"


Ellipse::Ellipse(const QPen & pen, const QBrush & brush,
                 AbstractShape * parent) : AbstractShape(pen, brush, parent),
                                           self(new QGraphicsEllipseItem),
                                           edge(new EdgeRectangle)

{
    _id = getId();
    name = getName();
}

Ellipse::~Ellipse()
{
    delete self;
    self = nullptr;

    delete edge;
    edge = nullptr;
}

int Ellipse::type() const
{
    return EllipseType::Type;
}

QRectF Ellipse::boundingRect() const
{
    return self->boundingRect();
}

QGraphicsItem * Ellipse::currentEdge() const
{
    return this->edge;
}

void Ellipse::normalize(qreal x1, qreal y1, qreal width)
{
    self->setPen(pen());
    self->setBrush(brush());
    self->setRect(x1, y1, width, width);
}

void Ellipse::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    self->setPen(pen());
    self->setBrush(brush());
    self->setRect(x1, y1, x2 - x1, y2 - y1);
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    QRectF tmp = boundingRect();
    painter->setPen(Qt::black);
    painter->drawText(tmp.center().x(), tmp.center().y(), name);

    self->paint(painter, option, widget);
}

QString Ellipse::getName() const
{
    return QString("Ellipse_").append(std::to_string(_id).c_str());
}

