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
                    enableResize(false),
                    edgeLocker(false),
                    currentScene(new Scene),
                    currentPen(QPen())
{
    setScene(currentScene);
    setMouseTracking(true);
}

Canvas::~Canvas()
{
    delete currentScene;
    currentScene = nullptr;
}

void Canvas::addShape(AbstractShape *shape)
{
    /*if(!shapeDrawn)
    {
        AbstractShape * undrawnShape = currentShape();
        currentScene->removeItem(undrawnShape);
        delete undrawnShape;
        undrawnShape = nullptr;
    }*/

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
            enableResize = false;
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
    if(enableResize)
    {
        QGraphicsItem * item = currentShape();
        if(item != nullptr)
        {
            QPointF p = event->pos();
            QRectF r = item->boundingRect();
            QPointF tl = mapFromScene(r.topLeft());
            QPointF br = mapFromScene(r.bottomRight());

            if((p.x() <= tl.x() && p.x() > tl.x() - 3) ||
                    (p.x() > br.x() - 3 && p.x() <= br.x()) &&
                    p.y() > tl.y() - 3 && p.y() < br.y())
            {
                setCursor(Qt::SizeHorCursor);
            }
            else if((p.y() <= tl.y() && p.y() > tl.y() - 3) ||
                    (p.y() > br.y() - 3 && p.y() <= br.y()) &&
                    p.x() > tl.x() - 3 && p.x() < br.x())
            {
                setCursor(Qt::SizeVerCursor);
            }
            else
            {
                setCursor(Qt::CrossCursor);
            }
        }
    }

    QPointF point = mapToScene(event->pos());

    if(event->buttons() & Qt::LeftButton)
    {
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
            edgeLocker = true;
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    if(buttonPressed)
    {

        if(edgeLocker)
        {
            currentScene->currentEdge()->setPen(currentPen);
            currentScene->currentEdge()->draw(startX(), startY(), endX(), endY());
            currentScene->update();
            edgeLocker = false;
        }

        shapeDrawn = true;
        buttonPressed = false;
        shapeSet = false;
        enableResize = true;
    }
}
