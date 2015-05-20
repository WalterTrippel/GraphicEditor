#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H


#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QPainter>

class AbstractShape : public QGraphicsItem
{
public:
    enum AbstractType { Type = UserType + 1};

    explicit AbstractShape(const QPen &pen = QPen(), const QBrush &brush = QBrush(),
                           QGraphicsItem * parent = nullptr);
    virtual ~AbstractShape();
    int type() const;
    virtual void setPen(const QPen &_pen);
    virtual void setBrush(const QBrush &_brush);
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual void draw(qreal x1, qreal y1, qreal x2, qreal y2) = 0;

    QPen pen() const;
    QBrush brush() const;

private:
    QPen _pen;
    QBrush _brush;
};

#endif // ABSTRACTSHAPE_H
