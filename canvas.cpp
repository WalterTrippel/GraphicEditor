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
                    coordinatesIterationMove(0, 0),
                    isMoved(false),
                    currentScene(new Scene),
                    currentPen(QPen()),
                    enableToRotate(false),
                    enableFill(false)
{
    setScene(currentScene);
    setMouseTracking(true);
    _direction = None;
    _normalize = NormalizeNone;
}

Canvas::~Canvas()
{
    delete currentScene;
    currentScene = nullptr;
}

void Canvas::hideNames()
{
    for(auto &i : currentScene->shapes)
    {
        i->name = "";
        i->update();
    }
    for(auto &i : currentScene->lines)
    {
        i->name = "";
        i->update();
    }
    currentScene->update();
}

void Canvas::showNames()
{
    for(auto &i : currentScene->shapes)
    {
        i->name = i->getName();
        i->update();
    }
    for(auto &i : currentScene->lines)
    {
        i->name = i->getName();
        i->update();
    }
    currentScene->update();
}

bool Canvas::isFill() const
{
    return enableFill;
}

void Canvas::setFill(bool flag)
{
    enableFill = flag;
}

void Canvas::removeCurrentEdge()
{
    /*EdgeRectangle * tmp = currentScene->currentEdge();
    if(tmp)
    {
        delete tmp;
        currentScene->update();
        tmp = nullptr;
    }*/
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

    if(shape->type() == LineSegment::LineSegmentType::Type)
    {
        currentScene->lines.append((LineSegment *)shape);
    }
    else
    {
        currentScene->shapes.append(shape);
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

bool Canvas::sceneLocker(QPointF point)
{
    if(point.x() < sceneRect().topLeft().x() + sceneError)
    {
        return false;
    }
    else if(point.y() < sceneRect().topLeft().y() + sceneError)
    {
        return false;
    }
    else if(point.x() > sceneRect().bottomRight().x() - sceneError)
    {
        return false;
    }
    else if(point.y() > sceneRect().bottomLeft().y() - sceneError)
    {
        return false;
    }
    return true;
}

void Canvas::checkIfProperRect(QPointF & tl, QPointF & br,
                               QPointF & tr, QPointF & bl)
{
    if(tl.x() > br.x() || tl.y() > br.y())
    {
        if(tl.x() > br.x() && tl.y() <= br.y())
        {
            std::swap(tl, tr);
            std::swap(br, bl);
        }
        else if(tl.y() > br.y() && tl.x() <= br.x())
        {
            std::swap(tl, bl);
            std::swap(br, tr);
        }
        else if(tl.x() > br.x() && tl.y() >= br.y())
        {
            std::swap(tl, br);
        }
    }
}

void Canvas::preventOverBoundingOnDraw(QPointF point, int & _endX, int & _endY)
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
}

void Canvas::preventOverBoundingOnMove(QRectF rect, QPointF increment)
{
    QPointF tl = mapFromScene(rect.topLeft());
    QPointF br = mapFromScene(rect.bottomRight());

    if(sceneLocker(rect.topLeft()) && sceneLocker(rect.topRight())
            && sceneLocker(rect.bottomRight()) && sceneLocker(rect.bottomLeft()))
    {
        _startX += increment.x();
        _startY += increment.y();
        _endX += increment.x();
        _endY += increment.y();
    }
    else
    {
        if(!sceneLocker(rect.bottomLeft()) && !sceneLocker(rect.topLeft())
                && !sceneLocker(rect.topRight()))
        {
            if(tl.x() < br.x() && tl.y() < br.y())
            {
                if(increment.x() > 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() < br.x() && tl.y() > br.y())
            {
                if(increment.x() > 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() < br.y())
            {
                if(increment.x() < 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() > br.y())
            {
                if(increment.x() < 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
        }
        else if(!sceneLocker(rect.topLeft()) && !sceneLocker(rect.topRight())
                && !sceneLocker(rect.bottomRight()))
        {
            if(tl.x() < br.x() && tl.y() < br.y())
            {
                if(increment.x() < 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() < br.x() && tl.y() > br.y())
            {
                if(increment.x() < 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() < br.y())
            {
                if(increment.x() > 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() > br.y())
            {
                if(increment.x() > 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
        }
        else if(!sceneLocker(rect.topRight()) && !sceneLocker(rect.bottomRight())
                && !sceneLocker(rect.bottomLeft()))
        {
            if(tl.x() < br.x() && tl.y() < br.y())
            {
                if(increment.x() < 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() < br.x() && tl.y() > br.y())
            {
                if(increment.x() < 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() < br.y())
            {
                if(increment.x() > 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() > br.y())
            {
                if(increment.x() > 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
        }
        else if(!sceneLocker(rect.bottomRight()) && !sceneLocker(rect.bottomLeft())
                && !sceneLocker(rect.topLeft()))
        {
            if(tl.x() < br.x() && tl.y() < br.y())
            {
                if(increment.x() > 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() < br.x() && tl.y() > br.y())
            {
                if(increment.x() > 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() < br.y())
            {
                if(increment.x() < 0 && increment.y() < 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
            else if(tl.x() > br.x() && tl.y() > br.y())
            {
                if(increment.x() < 0 && increment.y() > 0)
                {
                    _startX += increment.x();
                    _startY += increment.y();
                    _endX += increment.x();
                    _endY += increment.y();
                }
            }
        }
        else if(!sceneLocker(rect.topLeft()) && !sceneLocker(rect.bottomLeft()))
        {
            _startY += increment.y();
            _endY += increment.y();
            if(tl.x() < br.x())
            {
                if(increment.x() > 0)
                {
                    _startX += increment.x();
                    _endX += increment.x();
                }
            }
            else
            {
                if(increment.x() < 0)
                {
                    _startX += increment.x();
                    _endX += increment.x();
                }
            }
        }
        else if(!sceneLocker(rect.topLeft()) && !sceneLocker(rect.topRight()))
        {
            _startX += increment.x();
            _endX += increment.x();
            if(tl.y() < br.y())
            {
                if(increment.y() > 0)
                {
                    _startY += increment.y();
                    _endY += increment.y();
                }
            }
            else
            {
                if(increment.y() < 0)
                {
                    _startY += increment.y();
                    _endY += increment.y();
                }
            }
        }
        else if(!sceneLocker(rect.topRight()) && !sceneLocker(rect.bottomRight()))
        {
            _startY += increment.y();
            _endY += increment.y();
            if(tl.x() < br.x())
            {
                if(increment.x() < 0)
                {
                    _startX += increment.x();
                    _endX += increment.x();
                }
            }
            else
            {
                if(increment.x() > 0)
                {
                    _startX += increment.x();
                    _endX += increment.x();
                }
            }
        }
        else if(!sceneLocker(rect.bottomRight()) && !sceneLocker(rect.bottomLeft()))
        {
            _startX += increment.x();
            _endX += increment.x();
            if(tl.y() < br.y())
            {
                if(increment.y() < 0)
                {
                    _startY += increment.y();
                    _endY += increment.y();
                }
            }
            else
            {
                if(increment.y() > 0)
                {
                    _startY += increment.y();
                    _endY += increment.y();
                }
            }
        }
    }
}

bool Canvas::belongToFirstCorners(QPointF p, QPointF tl, QPointF br)
{
    if((p.x() <= tl.x() && p.x() > tl.x() - 3 &&
        p.y() <= tl.y() && p.y() > tl.y() - 3) ||
        p.x() <= br.x() && p.x() > br.x() - 3 &&
        p.y() <= br.y() && p.y() > br.y() - 3)
    {
        return true;
    }
    return false;
}

bool Canvas::belongToSecondCorners(QPointF p, QPointF tl, QPointF br)
{
    if( p.x() <= br.x() && p.x() > br.x() - 3 &&
        p.y() <= tl.y() && p.y() > tl.y() - 3 ||
        p.x() <= tl.x() && p.x() > tl.x() - 3 &&
        p.y() <= br.y() && p.y() > br.y() - 3)
    {
        return true;
    }
    return false;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(enableFill)
        {
            AbstractShape * tmp = currentShape();
            if(tmp->isUnderMouse())
            {
                tmp->setBrush(QBrush(color()));
                currentScene->update();
            }
        }
        else
        {
            QPointF point = mapToScene(event->pos());
            _startX = point.x();
            _startY = point.y();

            QGraphicsItem * item = currentShape();
            QPointF p = event->pos();
            QRectF r = item->boundingRect();

            QPointF tl = mapFromScene(r.topLeft());
            QPointF br = mapFromScene(r.bottomRight());
            QPointF tr = mapFromScene(r.topRight());
            QPointF bl = mapFromScene(r.bottomLeft());

            checkIfProperRect(tl, br, tr, bl);

            if(belongToFirstCorners(p, tl, br))
            {
                _direction = None;
                _normalize = NormalizeLeft;
            }
            /*else if(belongToSecondCorners(p, tl, br))
            {
                _direction = None;
                _normalize = NormalizeRight;
            }*/
            else if((p.x() <= tl.x() && p.x() > tl.x() - 3) &&
                    p.y() > tl.y() - 3 && p.y() < br.y())
            {
                _direction = Left;
                _startY = r.topLeft().y();
            }
            else if((p.x() > br.x() - 3 && p.x() <= br.x()) &&
                    p.y() > tl.y() - 3 && p.y() < br.y())
            {
                _direction = Right;
                _startX = r.topLeft().x();
                _startY = r.topLeft().y();
                _endY = r.bottomRight().y();
            }
            else if((p.y() <= tl.y() && p.y() > tl.y() - 3) &&
                    p.x() > tl.x() - 3 && p.x() < br.x())
            {
                _direction = Top;
                _startX = r.topLeft().x();
            }
            else if((p.y() > br.y() - 3 && p.y() <= br.y()) &&
                    p.x() > tl.x() - 3 && p.x() < br.x())
            {
                _direction = Bottom;
                _startX = r.topLeft().x();
                _startY = r.topLeft().y();
                _endX = r.bottomRight().x();
            }
            else if(p.x() >= tl.x() && p.x() <= br.x()
                    && p.y() >= tl.y() && p.y() <= br.y())
            {
                _direction = None;
                isMoved = true;
                _startX = item->boundingRect().topLeft().x();
                _startY = item->boundingRect().topLeft().y();
                _endX = item->boundingRect().bottomRight().x();
                _endY = item->boundingRect().bottomRight().y();
                coordinatesIterationMove = event->pos();
                linesEnds.clear();
                linesStarts.clear();
                linePointIndexes.clear();
                for(auto & i : currentScene->lines)
                {
                    if(i->boundingRect().intersects(currentShape()->boundingRect()))
                    {
                        QPointF tl = i->boundingRect().topLeft();
                        QPointF br = i->boundingRect().bottomRight();
                        if(currentShape()->boundingRect().contains(br) &&
                                !currentShape()->boundingRect().contains(tl))
                        {
                            linesEnds.append(br.toPoint());
                            linesStarts.append(tl.toPoint());
                            linePointIndexes.append(currentScene->lines.indexOf(i));
                        }
                        else if(currentShape()->boundingRect().contains(tl) &&
                                !currentShape()->boundingRect().contains(br))
                        {
                            linesEnds.append(tl.toPoint());
                            linesStarts.append(br.toPoint());
                            linePointIndexes.append(currentScene->lines.indexOf(i));
                        }
                    }
                }
            }
            else
            {
                _direction = None;

                currentScene->edge()->hide();
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
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(!enableFill)
    {
        if(!isMoved)
        {
            AbstractShape * item = currentShape();
            QPointF p = event->pos();
            QRectF r = item->boundingRect();

            QPointF tl = mapFromScene(r.topLeft());
            QPointF br = mapFromScene(r.bottomRight());
            QPointF tr = mapFromScene(r.topRight());
            QPointF bl = mapFromScene(r.bottomLeft());

            checkIfProperRect(tl, br, tr, bl);

            if(enableResize && shapeDrawn)
            {
                //checkIfProperRect(tl, br);
                if(item != nullptr && item->type() != AbstractShape::AbstractType::Type + 1)
                {

                    if(belongToFirstCorners(p, tl, br))
                    {
                        setCursor(Qt::SizeBDiagCursor);
                    }
                    /*else if(belongToSecondCorners(p, tl, br))
                    {
                        setCursor(Qt::SizeFDiagCursor);
                    }*/
                    else if(((p.x() <= tl.x() && p.x() > tl.x() - 3) &&
                        p.y() > tl.y() - 3 && p.y() < br.y()) ||
                        ((p.x() > br.x() - 3 && p.x() <= br.x()) &&
                        p.y() > tl.y() - 3 && p.y() < br.y()))
                    {
                        setCursor(Qt::SizeHorCursor);
                    }
                    else if(((p.y() > br.y() - 3 && p.y() <= br.y()) &&
                             p.x() > tl.x() - 3 && p.x() < br.x()) ||
                            (p.y() <= tl.y() && p.y() > tl.y() - 3) &&
                            p.x() > tl.x() - 3 && p.x() < br.x())
                    {
                        setCursor(Qt::SizeVerCursor);
                    }
                    else if(p.x() >= tl.x() && p.x() <= br.x()
                            && p.y() >= tl.y() && p.y() <= br.y())
                    {
                        setCursor(Qt::SizeAllCursor);
                    }
                    else
                    {
                        setCursor(Qt::CrossCursor);
                    }

                    if(event->buttons() & Qt::LeftButton)
                    {

                        QPointF tl = mapFromScene(r.topLeft());
                        QPointF br = mapFromScene(r.bottomRight());
                        QPointF point = mapToScene(event->pos());
                        switch(_direction)
                        {
                        case Left :
                        {
                            if(sceneLocker(point))
                            {
                                if(tl.x() > br.x())
                                {
                                    _endX = point.x();
                                }
                                else
                                {
                                    _startX = point.x();
                                }

                            }
                            break;
                        }

                        case Right :
                        {
                            if(sceneLocker(point))
                            {
                                if(tl.x() > br.x())
                                {
                                    _startX = point.x();
                                }
                                else
                                {
                                     _endX = point.x();
                                }
                            }
                            break;
                        }

                        case Top:
                        {
                            if(sceneLocker(point))
                            {
                                if(tl.y() > br.y())
                                {
                                    _endY = point.y();
                                }
                                else
                                {
                                    _startY = point.y();
                                }
                            }
                            break;
                        }
                        case Bottom :
                        {
                            if(sceneLocker(point))
                            {
                                if(tl.y() > br.y())
                                {
                                    _startY = point.y();
                                }
                                else
                                {
                                    _endY = point.y();
                                }
                            }
                            break;
                        }
                        }
                        item->draw(startX(), startY(), endX(), endY());
                        currentScene->edge()->draw(startX(), startY(),
                                                   endX(), endY());
                        currentScene->update();

                        switch(_normalize)
                        {
                        case NormalizeLeft:
                        {

                            _startX = point.x();
                            _startY = point.y();
                            item->normalize(point.x(), point.y(),
                                            point.x() - rect().topLeft().x());
                            QRectF tmp = item->boundingRect();
                            currentScene->edge()->draw(tmp.topLeft().x(), tmp.topLeft().y(),
                                                       tmp.bottomRight().x(), tmp.bottomRight().y());
                            _startX = tmp.topLeft().x();
                            _startY = tmp.topLeft().y();
                            _endX = tmp.bottomRight().x();
                            _endY = tmp.bottomRight().y();

                            if(item->type() == Triangle::TriangleType::Type)
                            {
                                ((Triangle*)item)->normalizeFlag = true;
                                _startX = point.x();
                                _startY = point.y();
                            }
                            break;
                        }
                        }
                    }
                }
            }

            QPointF point = mapToScene(event->pos());
            if(event->buttons() & Qt::LeftButton && _direction == None
                    && _normalize == NormalizeNone)
            {
                preventOverBoundingOnDraw(point, _endX, _endY);

                if(shapeSet)
                {
                    currentScene->currentShape()->setPen(currentPen);
                    currentScene->currentShape()->draw(startX(), startY(), endX(), endY());
                    currentScene->update();
                    edgeLocker = true;
                }
            }
        }
        else if((event->buttons() & Qt::LeftButton) && isMoved
                && currentScene->currentShape()->type()
                != LineSegment::LineSegmentType::Type)
        {
            QRectF r = currentShape()->boundingRect();
            QPoint tmp = QPoint(event->pos().x() -
                                coordinatesIterationMove.x(),
                                event->pos().y() -
                                coordinatesIterationMove.y());

            preventOverBoundingOnMove(r, tmp);
            currentScene->currentShape()->setPen(currentPen);
            if(currentShape()->type() == Triangle::TriangleType::Type &&
                    ((Triangle *)currentShape())->normalizeFlag)
            {
                currentScene->currentShape()->normalize(startX(), startY(),
                                startX() - rect().topLeft().x());
            }
            else
            {
                currentScene->currentShape()->draw(startX(), startY(), endX(), endY());
            }

            if(!linesEnds.isEmpty())
            {
                for(auto i: linePointIndexes)
                {
                    preventOverBoundingOnDraw(linesEnds[linePointIndexes.indexOf(i)],
                            linesEnds[linePointIndexes.indexOf(i)].rx(),
                            linesEnds[linePointIndexes.indexOf(i)].ry());
                    linesEnds[linePointIndexes.indexOf(i)] += tmp;
                    currentScene->lines.at(i)->draw(linesStarts[linePointIndexes.indexOf(i)].x(),
                            linesStarts[linePointIndexes.indexOf(i)].y(),
                            linesEnds[linePointIndexes.indexOf(i)].x(),
                            linesEnds[linePointIndexes.indexOf(i)].y());
                }
            }

            currentScene->edge()->hide();
            currentScene->update();
            coordinatesIterationMove = event->pos();
        }
    }
    else
    {
        AbstractShape * tmp = currentShape();
        if(tmp->isUnderMouse())
        {
            setCursor(Qt::PointingHandCursor);
        }
        else
        {
            setCursor(Qt::CrossCursor);
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{

    if(currentShape()->type() != LineSegment::LineSegmentType::Type)
    {
        AbstractShape * item = currentShape();
        currentScene->edge()->setPen(currentPen);
        QRectF tmp = item->boundingRect();
        currentScene->edge()->draw(tmp.topLeft().x(), tmp.topLeft().y(),
                                   tmp.bottomRight().x(), tmp.bottomRight().y());
        currentScene->edge()->show();
        currentScene->update();
        edgeLocker = false;
    }

    isMoved = false;
    if(enableFill)
    {
        enableFill = false;
        currentScene->currentShape()->setPen(currentPen);
        if(currentShape()->type() == Triangle::TriangleType::Type &&
                ((Triangle *)currentShape())->normalizeFlag)
        {
            currentScene->currentShape()->normalize(startX(), startY(),
                            startX() - rect().topLeft().x());
        }
        else
        {
            currentScene->currentShape()->draw(startX(), startY(), endX(), endY());
        }
        currentScene->update();
    }
    else
        _normalize = NormalizeNone;
    if(buttonPressed)
    {
        _direction = None;
        _normalize = NormalizeNone;

        isMoved = false;
        shapeDrawn = true;
        buttonPressed = false;
        shapeSet = false;
        enableResize = true;
    }
}
