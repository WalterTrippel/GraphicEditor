#include "canvas.h"

#include <QDebug>

Canvas::Canvas(QGraphicsView * parent) :
                    QGraphicsView(parent),
                    _startX(0),
                    _startY(0),
                    _endX(0),
                    _endY(0),
                    buttonPressed(false),
                    shapeSet(false),
                    shapeDrawn(true),
                    currentScene(new Scene),
                    currentPen(QPen())
{
    setScene(currentScene);
}

Canvas::~Canvas()
{
    delete currentScene;
    currentScene = nullptr;
}

void Canvas::addShape(AbstractShape *shape)
{
    if(!shapeDrawn)
    {
        AbstractShape * undrawnShape = currentShape();
        currentScene->removeItem(undrawnShape);
        delete undrawnShape;
        undrawnShape = nullptr;
    }

    currentScene->addItem(shape);
    shapeDrawn = false;
    shapeSet = true;
}

void Canvas::setSceneRect(qreal x, qreal y, qreal w, qreal h)
{
    currentScene->setSceneRect(x, y, w, h);

    qreal borderWidth = 0.5;
    QPen borderPen(QBrush(Qt::black), borderWidth);
    borderPen.setCapStyle(Qt::SquareCap);
    borderPen.setJoinStyle(Qt::MiterJoin);

    qreal shadowWidth = 5;
    QPen shadowPen(QBrush(Qt::lightGray), shadowWidth);
    shadowPen.setCapStyle(Qt::SquareCap);
    shadowPen.setJoinStyle(Qt::MiterJoin);

    QGraphicsItemGroup * group = new QGraphicsItemGroup;

    QGraphicsLineItem * shadowRight =
            new QGraphicsLineItem(x + w + (shadowWidth - borderWidth) / 2,
                                  y + shadowWidth,
                                  x + w + (shadowWidth - borderWidth) / 2,
                                  y + h + shadowWidth / 2);
    shadowRight->setPen(shadowPen);

    QGraphicsLineItem * shadowBottom =
            new QGraphicsLineItem(x + shadowWidth,
                                  y + h + (shadowWidth - borderWidth) / 2,
                                  x + w + shadowWidth / 2,
                                  y + h + (shadowWidth - borderWidth) / 2);
    shadowBottom->setPen(shadowPen);

    QGraphicsRectItem * rect = new QGraphicsRectItem(x, y, w, h);
    rect->setPen(borderPen);

    group->addToGroup(shadowRight);
    group->addToGroup(shadowBottom);
    group->addToGroup(rect);

    currentScene->addItem(group);
}

AbstractShape * Canvas::currentShape()
{
    return (AbstractShape *)currentScene->items().first();
}

void Canvas::setColor(QColor color)
{
    currentPen.setColor(color);
}

QColor Canvas::color() const
{
    return currentPen.color();
}

void Canvas::setWidth(int width)
{
    currentPen.setWidth(width);
}

int Canvas::width() const
{
    return currentPen.width();
}

void Canvas::clear()
{
    currentScene->clear();
}

int Canvas::startX() const
{
    return _startX;
}

int Canvas::startY() const
{
    return _startY;
}

int Canvas::endX() const
{
    return _endX;
}

int Canvas::endY() const
{
    return _endY;
}

QRectF Canvas::drawRect() const
{
    QPoint first = mapFromScene(QPointF(currentScene->sceneRect().topLeft().x(),
                                currentScene->sceneRect().topLeft().y()));
    QPoint second = mapFromScene(QPointF(currentScene->sceneRect().bottomRight().x(),
                                currentScene->sceneRect().bottomRight().y()));

    QRectF rect(first, second);

    return rect;
}

void Canvas::registerObserver(CanvasObserver *observer)
{
    canvasObservers.append(observer);
}

void Canvas::removeObserver(CanvasObserver *observer)
{
    CanvasObserver * tmp = observer;
    canvasObservers.removeOne(observer);
    delete tmp;
    tmp = nullptr;
}

void Canvas::notifyObservers()
{
    for(auto i : canvasObservers)
    {
        i->drawSameShapeType();
    }
}

QPoint * Canvas::borderIntersection(int first_x, int first_y, int second_x, int second_y,
                                    int third_x, int third_y, int fourth_x, int fourth_y) const
{
    int firstVector_x = 0, firstVector_y = 0, secondVector_x = 0, secondVector_y = 0;
    firstVector_x = second_x - first_x;
    firstVector_y = second_y - first_y;

    secondVector_x = fourth_x - third_x;
    secondVector_y = fourth_y - third_y;

    float s = 0.0f, t = 0.0f;
    s = (-firstVector_y * (first_x - third_x) + firstVector_x * (first_y - third_y)) /
            (-secondVector_x * firstVector_y + firstVector_x * secondVector_y);
    t = (secondVector_x * (first_y - third_y) + secondVector_y * (first_x - third_x)) /
            (-secondVector_x * firstVector_y + firstVector_x * secondVector_y);

    t = abs(t);
    if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        return new QPoint(first_x + (t * firstVector_x), first_y + (t * firstVector_y));
    }
    return nullptr;
}

qreal Canvas::angleVectors(int first_x, int first_y, int second_x, int second_y) const
{
    int tmp = first_x * second_x + first_y * second_y;
    const int buff = sqrt(first_x * first_x + first_y * first_y) * sqrt(second_x * second_x + second_y * second_y);

    tmp = tmp / buff;

    return acos(tmp);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF point = mapToScene(event->pos());
        _startX = point.x();
        _startY = point.y();

        if(point.x() > sceneRect().topLeft().x()
                && point.y() > sceneRect().topLeft().y()
                && point.x() < sceneRect().bottomRight().x()
                && point.y() < sceneRect().bottomRight().y())
        {
            buttonPressed = true;
            if(shapeDrawn)
            {
                notifyObservers();
            }
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF point = mapToScene(event->pos());

        if(point.x() > sceneRect().topLeft().x()
                && point.y() > sceneRect().topLeft().y()
                && point.x() < sceneRect().bottomRight().x()
                && point.y() < sceneRect().bottomRight().y())
        {
            _endX = point.x();
            _endY = point.y();
        }
        else
        {
            if(point.x() < sceneRect().topLeft().x())
            {
                if(point.y() < sceneRect().topLeft().y())
                {
                    _endX = sceneRect().topLeft().x();
                    _endY = sceneRect().topLeft().y();
                }
                else if(point.y() > sceneRect().bottomLeft().y())
                {
                    _endX = sceneRect().topLeft().x();
                    _endY = sceneRect().bottomLeft().y();
                }
                else
                {
                    _endX = sceneRect().topLeft().x();
                    _endY = point.y();
                }
            }
            else if(point.y() < sceneRect().topLeft().y())
            {
                if(point.x() > sceneRect().bottomRight().x())
                {
                    _endX = sceneRect().bottomRight().x();
                    _endY = sceneRect().topLeft().y();
                }
                else
                {
                    _endX = point.x();
                    _endY = sceneRect().topLeft().y();
                }
            }
            else if(point.x() > sceneRect().bottomRight().x())
            {
                if(point.y() > sceneRect().bottomRight().y())
                {
                    _endX = sceneRect().bottomRight().x();
                    _endY = sceneRect().bottomLeft().y();
                }
                else
                {
                    _endX = sceneRect().bottomRight().x();
                    _endY = point.y();
                }
            }
            else if(point.y() > sceneRect().bottomLeft().y())
            {
                if(point.x() < sceneRect().bottomLeft().x())
                {
                    _endX = sceneRect().bottomLeft().x();
                    _endY = sceneRect().bottomLeft().y();
                }
                else
                {
                    _endX = point.x();
                    _endY = sceneRect().bottomRight().y();
                }
            }
        }

        if(shapeSet)
        {
            currentScene->currentShape()->setPen(currentPen);
            currentScene->currentShape()->draw(startX(), startY(), endX(), endY());
            currentScene->update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    if(buttonPressed)
    {
        shapeDrawn = true;
        buttonPressed = false;
        shapeSet = false;

    }
}
