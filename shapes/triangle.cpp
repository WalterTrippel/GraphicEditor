#include "triangle.h"

Triangle::Triangle(const QPen & pen, const QBrush & brush,
                     AbstractShape * parent): AbstractShape(pen, brush, parent),
                                              self(new QGraphicsPolygonItem),
                                              edge(new EdgeRectangle)
{
}

Triangle::~Triangle()
{
    delete self;
    self = nullptr;

    delete edge;
    edge = nullptr;
}

int Triangle::type() const
{
    return TriangleType::Type;
}

QGraphicsItem * Triangle::currentEdge() const
{
    return this->edge;
}

QRectF Triangle::boundingRect() const
{
    return self->boundingRect();
}

void Triangle::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    self->setPen(pen());
    self->setBrush(brush());

    QPolygonF tmp;
    tmp.append(QPointF(x1, y1));
    tmp.append(QPointF(x2, y2));
    tmp.append(QPointF((x1 + x2) / 2, y1 + (x1 - x2)));
    self->setPolygon(tmp);

    //self->setRect(x1, y1, x2 - x1, y2 - y1);
}

void Triangle::normalize(qreal x1, qreal y1, qreal width)
{
    self->setPen(pen());
    self->setBrush(brush());

    //self->setRect(x1, y1, width, width);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    self->paint(painter, option, widget);
}
