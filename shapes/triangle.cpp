#include "triangle.h"

Triangle::Triangle(const QPen & pen, const QBrush & brush,
                     AbstractShape * parent): AbstractShape(pen, brush, parent),
                                              self(new QGraphicsPolygonItem),
                                              edge(new EdgeRectangle),
                                              normalizeFlag(false)
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
    tmp.append(QPointF((x1 + x2) / 2, y1));
    self->setPolygon(tmp);

}

void Triangle::normalize(qreal x1, qreal y1, qreal width)
{
    self->setPen(pen());
    self->setBrush(brush());

    qreal s60 = sin(60 * M_PI / 180);
    qreal c60 = cos(60 * M_PI / 180);

    QPointF third = QPointF(c60 * (-width) + x1 + width,
                            s60 * (-width) + y1);
    QPolygonF tmp;
    tmp.append(QPointF(x1, y1));
    tmp.append(QPointF(x1 + width, y1));
    tmp.append(third);
    self->setPolygon(tmp);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    self->paint(painter, option, widget);
}
