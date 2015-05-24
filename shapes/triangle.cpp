#include "triangle.h"

Triangle::Triangle(const QPen & pen, const QBrush & brush,
                     AbstractShape * parent): AbstractShape(pen, brush, parent),
                                              self(new QGraphicsPolygonItem),
                                              edge(new EdgeRectangle),
                                              normalizeFlag(false)
{
    _id = getId();
    name = getName();
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
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

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
    QRectF tmp = boundingRect();
    painter->setPen(Qt::black);
    painter->drawText(tmp.center().x(), tmp.center().y(), name);

    self->paint(painter, option, widget);
}

QString Triangle::getName() const
{
    return QString("Triangle_").append(std::to_string(_id).c_str());
}
