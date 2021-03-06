#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <math.h>

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
    virtual QGraphicsItem * currentEdge() const = 0;

    virtual void normalize(qreal x1, qreal y1, qreal width) = 0;

    virtual long getId() const;
    virtual QString  getName() const = 0;

    //virtual int getWidth() const = 0;
    //virtual int getHeight() const = 0;

    QPen pen() const;
    QBrush brush() const;
    QString name;

private:
    QPen _pen;
    QBrush _brush;
    long id;
};

#endif // ABSTRACTSHAPE_H
