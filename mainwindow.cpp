#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lastDrawnShapeType = None;

    buttonCheckStates.append(ui->bDrawLine);
    buttonCheckStates.append(ui->bDrawRectangle);
    buttonCheckStates.append(ui->bDrawEllipse);
    buttonCheckStates.append(ui->bDrawText);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

    connect(ui->bPenColor, SIGNAL(released()), this, SLOT(buttonPenColorAction()));
    connect(ui->bDrawLine, SIGNAL(released()), this, SLOT(buttonLineAction()));
    connect(ui->bDrawRectangle, SIGNAL(released()), this, SLOT(buttonRectAction()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawSameShapeType()
{
    AbstractShape * lastDrawnShape = this->lastDrawnShape();
    if(lastDrawnShape)
    {
        ((Canvas*)ui->tabWidget->currentWidget())->addShape((AbstractShape *)lastDrawnShape->currentEdge());
        ((Canvas*)ui->tabWidget->currentWidget())->addShape(lastDrawnShape);
    }
    lastDrawnShape = nullptr;
}

void MainWindow::checkSwitcher(QPushButton * button)
{
    for(auto &i : buttonCheckStates)
    {
        if(button != i && i->isChecked())
        {
            i->setChecked(false);
        }
    }
}

AbstractShape * MainWindow::lastDrawnShape() const
{
    switch(lastDrawnShapeType)
    {
    case Line: return new LineSegment;
        break;
    case RectangleType: return new Rectangle;
        break;
    default: return nullptr;
        break;
    }
}

void MainWindow::newImage()
{
    Canvas * canvas = new Canvas;
    canvas->registerObserver(this);

    bool valideName;

    QString imageName = QInputDialog::getText(this, tr("Enter Name"),
                                              tr("Image Name : "), QLineEdit::Normal,
                                              "", &valideName);
    if(valideName)
    {
        if(!imageName.isEmpty())
        {
            ui->tabWidget->addTab(canvas, imageName);
        }
        else
        {
            ui->tabWidget->addTab(canvas, tr("untitled"));
        }
    }
    else
    {
        return;
    }

    QPoint imageSize;
    imageSize.setX(QInputDialog::getInt(this, tr("Enter width"), tr("Image width metrics in px")));
    imageSize.setY(QInputDialog::getInt(this, tr("Enter height"), tr("Image height metrics in px")));

    if(imageSize.x() && imageSize.y())
    {
        canvas->setSceneRect(0, 0, imageSize.x(), imageSize.y());
    }
    else
    {
        canvas->setSceneRect(0, 0, 250, 250); // set const
    }
    canvas->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
}

void MainWindow::buttonLineAction()
{
    checkSwitcher(ui->bDrawLine);

    if(ui->tabWidget->currentWidget())
    {
        lastDrawnShapeType = Line;

        ((Canvas *)ui->tabWidget->currentWidget())->addShape((AbstractShape *)lastDrawnShape()->currentEdge());
        ((Canvas *)ui->tabWidget->currentWidget())->addShape(lastDrawnShape());
    }
}

void MainWindow::buttonRectAction()
{
    checkSwitcher(ui->bDrawRectangle);

    if(ui->tabWidget->currentWidget())
    {
        lastDrawnShapeType = RectangleType;

        ((Canvas *)ui->tabWidget->currentWidget())->addShape((AbstractShape *)lastDrawnShape()->currentEdge());
        ((Canvas *)ui->tabWidget->currentWidget())->addShape(lastDrawnShape());
    }
}

void MainWindow::buttonPenColorAction()
{
    if(ui->tabWidget->currentWidget())
    {
        QColor color(QColorDialog::getColor(((Canvas *)ui->tabWidget->currentWidget())->color()));

        ((Canvas *)ui->tabWidget->currentWidget())->setColor(color);
    }
}