#ifndef CANVAS_H
#define CANVAS_H

#define sceneError 3

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include "abstractshape.h"
#include "scene.h"
#include "canvasobserver.h"

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canvas(QGraphicsView * parent = 0);
    ~Canvas();

    enum ResizeDirection {None, Left, Top, Right, Bottom};

    void addShape(AbstractShape * shape);
    //void addBackgroundShape(AbstractShape * backgroundShape);
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);
    AbstractShape * currentShape();
    void setColor(QColor color);
    QColor color() const;

    int startX() const;
    int startY() const;
    int endX() const;
    int endY() const;

    //pen width
    void setWidth(int width);
    int width() const;
    void clear();
    QRectF drawRect() const;
    void registerObserver(CanvasObserver * observer);
    void removeObserver(CanvasObserver * observer);
    bool sceneLocker(QPointF point);

private:
    ResizeDirection _direction;

    int _startX;
    int _startY;
    int _endX;
    int _endY;
    bool buttonPressed;
    bool shapeSet;
    bool shapeDrawn;
    bool enableResize;
    bool edgeLocker;
    qreal resizeTranslate;
    Scene * currentScene;
    QPen currentPen;

    QList<CanvasObserver *> canvasObservers;

    void notifyObservers();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // CANVAS_H
