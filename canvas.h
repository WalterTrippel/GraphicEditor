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
#include "shapes/rectangle.h"
#include "shapes/linesegment.h"
#include "shapes/triangle.h"

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canvas(QGraphicsView * parent = 0);
    ~Canvas();

    enum ResizeDirection {None, Left, Top, Right, Bottom};

    enum NormalizeDirection {NormalizeNone, NormalizeLeft, NormalizeRight};

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
    bool isFill() const;
    void setFill(bool flag);
    void clear();
    QRectF drawRect() const;
    void registerObserver(CanvasObserver * observer);
    void removeObserver(CanvasObserver * observer);
    bool sceneLocker(QPointF point);
    void removeCurrentEdge();

    void showNames();
    void hideNames();

    void makeCurrentByName(QString name);


signals:
    void addName(QString);

private:
    ResizeDirection _direction;
    NormalizeDirection _normalize;

    int _startX;
    int _startY;
    int _endX;
    int _endY;
    bool buttonPressed;
    bool shapeSet;
    bool shapeDrawn;
    bool enableResize;
    bool edgeLocker;
    QPoint coordinatesIterationMove;
    bool isMoved;
    Scene * currentScene;
    QPen currentPen;
    bool enableToRotate;
    bool enableFill;

    void checkIfProperRect(QPointF & tl, QPointF & br, QPointF & tr, QPointF & bl);
    void preventOverBoundingOnDraw(QPointF point, int & _endX, int & _endY);
    void preventOverBoundingOnMove(QRectF rect, QPointF increment);

    bool belongToFirstCorners(QPointF point, QPointF tl, QPointF br);
    bool belongToSecondCorners(QPointF point, QPointF tl, QPointF br);


    QList<CanvasObserver *> canvasObservers;
    QList<QPoint> linesEnds;
    QList<QPoint> linesStarts;
    QList<int> linePointIndexes;

    void notifyObservers();

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // CANVAS_H
