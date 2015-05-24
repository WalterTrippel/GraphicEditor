#include "rectangle.h"

#include <QDebug>

Rectangle::Rectangle(const QPen & pen, const QBrush & brush,
                     AbstractShape * parent): AbstractShape(pen, brush, parent),
                                              self(new QGraphicsRectItem),
                                              edge(new EdgeRectangle)
{
    _id = getId();
    name = getName();
}

Rectangle::~Rectangle()
{
    delete self;
    self = nullptr;

    delete edge;
    edge = nullptr;
}

int Rectangle::type() const
{
    return RectangleType::Type;
}

QGraphicsItem * Rectangle::currentEdge() const
{
    return this->edge;
}

QRectF Rectangle::boundingRect() const
{
    #define angle rotation()

    QRectF tmp = self->boundingRect();
    int centerX = (tmp.topLeft().x() + tmp.bottomRight().x()) / 2;
    int centerY = (tmp.topLeft().y() + tmp.bottomRight().y()) / 2;
    QPointF topLeft = QPoint(centerX + (tmp.topLeft().x() - centerX) * cos(angle)
            - (tmp.topLeft().x() - centerY) * sin(angle),
            centerY + (tmp.topLeft().y() - centerY) * cos(angle)
            + (tmp.topLeft().x() - centerX) * sin(angle));
    QPointF topRight = QPoint(centerX + (tmp.topRight().x() - centerX) * cos(angle)
            - (tmp.topRight().x() - centerY) * sin(angle),
            centerY + (tmp.topRight().y() - centerY) * cos(angle)
            + (tmp.topRight().x() - centerX) * sin(angle));
    QPointF bottomRight = QPoint(centerX + (tmp.bottomRight().x() - centerX) * cos(angle)
            - (tmp.bottomRight().x() - centerY) * sin(angle),
            centerY + (tmp.bottomRight().y() - centerY) * cos(angle)
            + (tmp.bottomRight().x() - centerX) * sin(angle));
    QPointF bottomLeft = QPoint(centerX + (tmp.bottomLeft().x() - centerX) * cos(angle)
            - (tmp.bottomLeft().x() - centerY) * sin(angle),
            centerY + (tmp.bottomLeft().y() - centerY) * cos(angle)
            + (tmp.bottomLeft().x() - centerX) * sin(angle));

    QPointF newTopLeft = QPointF(topLeft.x(), topRight.y());
    QPointF newBottomRight = QPointF(bottomRight.x(), bottomLeft.y());

    tmp = QRectF(newTopLeft, newBottomRight);
    return tmp;
}

void Rectangle::draw(qreal x1, qreal y1, qreal x2, qreal y2)
{
    self->setPen(pen());
    self->setBrush(brush());

    self->setRect(x1, y1, x2 - x1, y2 - y1);
}

void Rectangle::normalize(qreal x1, qreal y1, qreal width)
{
    self->setPen(pen());
    self->setBrush(brush());

    self->setRect(x1, y1, width, width);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF tmp = boundingRect();
    painter->setPen(Qt::black);

    painter->drawText(tmp.center().x(), tmp.center().y(), name);

    self->paint(painter, option, widget);
}

QString Rectangle::getName() const
{
    return QString("Rectangle_").append(std::to_string(_id).c_str());
}

