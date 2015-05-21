#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMouseEvent>
#include <QLabel>
#include <QFrame>
#include <QPainter>
#include <QScrollArea>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QColorDialog>
#include <QFileDialog>
#include "canvas.h"
#include "canvasobserver.h"

#include "shapes/linesegment.h"
#include "shapes/rectangle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public CanvasObserver
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void drawSameShapeType() final;

private:
    Ui::MainWindow *ui;

    enum Shapes {None, Line, RectangleType, Ellipse, Triangle, Text};

    Shapes lastDrawnShapeType;
    QList<QPushButton *> buttonCheckStates;

    AbstractShape * lastDrawnShape() const;
    void checkSwitcher(QPushButton * button);

private slots:
    void newImage();
    void buttonLineAction();
    void buttonRectAction();


    void buttonPenColorAction();
    //void buttonPenWidthAction();

    //void closeTab();
    //void closeTab(int tabIndex);
    //void buttonDrawRectangle
};

#endif // MAINWINDOW_H