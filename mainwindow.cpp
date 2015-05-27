#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lastDrawnShapeType = None;

    buttonCheckStates.append(ui->bDrawLine);
    buttonCheckStates.append(ui->bDrawRectangle);
    buttonCheckStates.append(ui->bDrawEllipse);
    buttonCheckStates.append(ui->bTriangle);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

    ui->rShowName->setChecked(true);
    ui->rHideName->setChecked(false);

    connect(ui->bPenColor, SIGNAL(released()), this, SLOT(buttonPenColorAction()));
    connect(ui->bDrawLine, SIGNAL(released()), this, SLOT(buttonLineAction()));
    connect(ui->bDrawRectangle, SIGNAL(released()), this, SLOT(buttonRectAction()));
    connect(ui->bDrawEllipse, SIGNAL(released()), this, SLOT(buttonEllipseAction()));
    connect(ui->bPenWidth, SIGNAL(released()), this, SLOT(buttonPenWidthAction()));
    connect(ui->bTriangle, SIGNAL(released()), this, SLOT(buttonTriangleAction()));
    connect(ui->bFill, SIGNAL(released()), this, SLOT(buttonFill()));
    connect(ui->rShowName, SIGNAL(clicked(bool)), this, SLOT(showNames()));
    connect(ui->rHideName, SIGNAL(clicked(bool)), this, SLOT(hideNames()));
    connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemDoubleClicked(QModelIndex)));
    connect(ui->listWidget, SIGNAL(activated(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
    connect(ui->actionShow_List_View, SIGNAL(triggered(bool)), this, SLOT(showTableList()));
    connect(ui->action_Hide_List_View, SIGNAL(triggered(bool)), this, SLOT(hideTableList()));
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
        //((Canvas*)ui->tabWidget->currentWidget())->addShape((AbstractShape *)lastDrawnShape->currentEdge());
        ((Canvas*)ui->tabWidget->currentWidget())->addShape(lastDrawnShape);
    }
    lastDrawnShape = nullptr;
}

void MainWindow::checkSwitcher(QPushButton * button)
{
    if(lastDrawnShape())
    {
        ((Canvas *)ui->tabWidget->currentWidget())->removeCurrentEdge();
    }
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
    case Line:
    {
        LineSegment * tmp = new LineSegment;
        return tmp;
        break;
    }
    case RectangleType:
    {
        return new RectangleShape;
        break;
    }
    case EllipseType:
    {
        return new EllipseShape;
        break;
    }
    case TriangleType:
    {
        return new Triangle;
        break;
    }
    default:
    {
        return nullptr;
        break;
    }
    }
}

void MainWindow::newImage()
{
    Canvas * canvas = new Canvas;
    canvas->registerObserver(this);

    bool valideName;

    QString imageName = QInputDialog::getText(this, tr("Name"),
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
    imageSize.setX(QInputDialog::getInt(this, tr("Width"), tr("Image width metrics in px")));
    imageSize.setY(QInputDialog::getInt(this, tr("Height"), tr("Image height metrics in px")));

    if(imageSize.x() && imageSize.y())
    {
        canvas->setSceneRect(0, 0, imageSize.x(), imageSize.y());
    }
    else
    {
        canvas->setSceneRect(0, 0, 250, 250);
    }
    canvas->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
    //canvas->addShape(new LineSegment);
    connect((Canvas*)ui->tabWidget->currentWidget(), SIGNAL(addName(QString)), this, SLOT(addedItem(QString)));
}

void MainWindow::buttonLineAction()
{
    checkSwitcher(ui->bDrawLine);

    if(ui->tabWidget->currentWidget())
    {
        lastDrawnShapeType = Line;

        ((Canvas *)ui->tabWidget->currentWidget())->addShape(lastDrawnShape());
    }
}

void MainWindow::buttonRectAction()
{
    checkSwitcher(ui->bDrawRectangle);

    if(ui->tabWidget->currentWidget())
    {
        lastDrawnShapeType = RectangleType;

        ((Canvas *)ui->tabWidget->currentWidget())->addShape(lastDrawnShape());
    }
}

void MainWindow::buttonEllipseAction()
{
    checkSwitcher(ui->bDrawEllipse);

    if(ui->tabWidget->currentWidget())
    {
        lastDrawnShapeType = EllipseType;

        ((Canvas *)ui->tabWidget->currentWidget())->addShape(lastDrawnShape());
    }
}

void MainWindow::buttonTriangleAction()
{
    checkSwitcher(ui->bTriangle);

    if(ui->tabWidget->currentWidget())
    {
        lastDrawnShapeType = TriangleType;

        ((Canvas*)ui->tabWidget->currentWidget())->addShape(lastDrawnShape());
    }
}

void MainWindow::buttonFill()
{
    if(ui->tabWidget->currentWidget())
    {
        if(((Canvas*)ui->tabWidget->currentWidget())->isFill())
        {
            ((Canvas*)ui->tabWidget->currentWidget())->setFill(false);
        }
        else
        {
            ((Canvas*)ui->tabWidget->currentWidget())->setFill(true);
        }
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

void MainWindow::buttonPenWidthAction()
{
    if(ui->tabWidget->currentWidget())
    {
        int width(QInputDialog::getInt(this, tr("Enter Pen Width"), tr("Pen Width, px")));
        ((Canvas*)ui->tabWidget->currentWidget())->setWidth(width);
    }
}

void MainWindow::showNames()
{
    ui->rHideName->setChecked(false);

    Canvas * tmp = (Canvas*)ui->tabWidget->currentWidget();
    if(tmp)
        ((Canvas*)ui->tabWidget->currentWidget())->showNames();
}

void MainWindow::hideNames()
{
    ui->rShowName->setChecked(false);

    Canvas * tmp = (Canvas*)ui->tabWidget->currentWidget();
    if(tmp)
        ((Canvas*)ui->tabWidget->currentWidget())->hideNames();
}

void MainWindow::itemDoubleClicked(QModelIndex index)
{
    //QMessageBox::information(this, "Hi", "Clicked " + index.data().toString());
    ConfigDialog * dialog = new ConfigDialog;
    dialog->show();

    connect(dialog, SIGNAL(sendItemDeleted()), this, SLOT(receiveItemDeleted()));
    connect(dialog, SIGNAL(sendItemUpdated(QBrush)), this, SLOT(receiveItemUpdated(QBrush)));
}

void MainWindow::addedItem(QString name)
{
    ui->listWidget->addItem(name);
}

void MainWindow::deleteItem(QModelIndex index)
{
    ui->listWidget->removeItemWidget(ui->listWidget->item(index.row()));
}

void MainWindow::closeTab(int tabindex)
{
    ui->listWidget->clear();
    ui->tabWidget->removeTab(tabindex);
    //((Canvas *)ui->tabWidget->currentWidget())->deleteAllItemsOnPage();
}

void MainWindow::closeTab()
{
    closeTab(ui->tabWidget->currentIndex());
}

void MainWindow::itemClicked(QModelIndex index)
{
    QString name = index.data().toString();
    ((Canvas*)ui->tabWidget->currentWidget())->makeCurrentByName(name);
}

void MainWindow::receiveItemDeleted()
{
    delete ui->listWidget->currentItem();
    ((Canvas*)ui->tabWidget->currentWidget())->removeCurrentItem();
}

void MainWindow::receiveItemUpdated(QBrush brush)
{
    ((Canvas *)ui->tabWidget->currentWidget())->currentShape()->setBrush(brush);
    ((Canvas *)ui->tabWidget->currentWidget())->updateScene();
}

void MainWindow::showTableList()
{
    ui->actionShow_List_View->setChecked(true);
    ui->action_Hide_List_View->setChecked(false);
    ui->dockWidget->show();
}

void MainWindow::save()
{
    QString currentDirSave = "";
    if((Canvas *)ui->tabWidget->currentWidget())
    {
        QRect currentRect = ((Canvas*)ui->tabWidget->currentWidget())->viewport()->rect();
        ((Canvas*)ui->tabWidget->currentWidget())->adjustSize();

        QRect rect = ((Canvas*)ui->tabWidget->currentWidget())->drawRect().toRect();

        QPixmap pixmap(rect.width(), rect.height());

        QPainter painter(&pixmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        ((Canvas*)ui->tabWidget->currentWidget())->render(&painter, rect, rect);
        painter.end();

        ((Canvas*)ui->tabWidget->currentWidget())->resize(currentRect.width(), currentRect.height());

        QString selfilter = tr("JPEG (*.jpg *.jpeg)");
        QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save Dialog"),
                currentDirSave,
                tr("All files (*.*);;JPEG (*.jpg *.jpeg);;PNG (*.png);;XML (*.xml)" ),
                &selfilter
        );

        if(!fileName.isEmpty())
        {
            if(selfilter == "JPEG (*.jpg *.jpeg)" || selfilter == "PNG (*.png)")
            {
                if(selfilter == "JPEG (*.jpg *.jpeg)")
                {
                    fileName += ".jpg";
                }
                else
                {
                    fileName += ".png";
                }
                QStringList list = fileName.split("/");
                for(int i = 0; i < list.size() - 1; ++i)
                {
                    currentDirSave += list.at(i) + "/";
                }

                QStringList listFormat = fileName.split(".");
                const char * format = listFormat.at(listFormat.size() - 1).toStdString().c_str();

                pixmap.save(fileName, format);
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), list.at(list.size() - 1));
            }
            else if(selfilter == "XML (*.xml)")
            {
                fileName += ".xml";
                QFile _file(fileName);
                _file.open(QIODevice::WriteOnly | QIODevice::Text);
                QXmlStreamWriter writer(&_file);

                writer.setAutoFormatting(true);
                writer.writeStartDocument("1.0");
                writer.writeComment("I am a good old rebel");

                Canvas * current = (Canvas *)ui->tabWidget->currentWidget();
                Scene * tmpScene = current->getCurrentScene();
                if(tmpScene)
                {
                    writer.writeStartElement("scene");
                    writer.writeStartElement("rect");
                    writer.writeStartElement("topLeft");
                    writer.writeAttribute("x",
                            QString::number(currentRect.topLeft().x()));
                    writer.writeAttribute("y",
                            QString::number(currentRect.topLeft().y()));
                    writer.writeEndElement();
                    writer.writeStartElement("bottomRight");
                    writer.writeAttribute("x",
                            QString::number(currentRect.bottomRight().x()));
                    writer.writeAttribute("y",
                            QString::number(currentRect.bottomRight().y()));
                    writer.writeEndElement();
                    writer.writeEndElement();
                    writer.writeEndElement();

                    for(auto &i : tmpScene->shapes)
                    {
                        writer.writeStartElement("shape");
                        writer.writeStartElement("rect");
                        writer.writeStartElement("topLeft");
                        writer.writeAttribute("x",
                                QString::number(i->boundingRect().topLeft().x()));
                        writer.writeAttribute("y",
                                QString::number(i->boundingRect().topLeft().y()));
                        writer.writeEndElement();
                        writer.writeStartElement("bottomRight");
                        writer.writeAttribute("x",
                                QString::number(i->boundingRect().bottomRight().x()));
                        writer.writeAttribute("y",
                                QString::number(i->boundingRect().bottomRight().y()));
                        writer.writeEndElement();
                        writer.writeEndElement();
                        writer.writeStartElement("brush");
                        writer.writeAttribute("color",
                                QString::number(i->brush().color().value()));
                        writer.writeEndElement();
                        writer.writeStartElement("pen");
                        writer.writeAttribute("color", QString::number(i->pen().color().value()));
                        writer.writeAttribute("width", QString::number(i->pen().width()));
                        writer.writeEndElement();
                        writer.writeTextElement("ShapeType", QString::number(i->type()));
                        writer.writeEndElement();
                        writer.writeEndDocument();
                    }

                    for(auto &i : tmpScene->lines)
                    {
                        writer.writeStartElement("shape");
                        writer.writeStartElement("rect");
                        writer.writeStartElement("topLeft");
                        writer.writeAttribute("x",
                                QString::number(i->boundingRect().topLeft().x()));
                        writer.writeAttribute("y",
                                QString::number(i->boundingRect().topLeft().y()));
                        writer.writeEndElement();
                        writer.writeStartElement("bottomRight");
                        writer.writeAttribute("x",
                                QString::number(i->boundingRect().bottomRight().x()));
                        writer.writeAttribute("y",
                                QString::number(i->boundingRect().bottomRight().y()));
                        writer.writeEndElement();
                        writer.writeEndElement();
                        writer.writeStartElement("brush");
                        writer.writeAttribute("color",
                                QString::number(i->brush().color().value()));
                        writer.writeEndElement();
                        writer.writeStartElement("pen");
                        writer.writeAttribute("color", QString::number(i->pen().color().value()));
                        writer.writeAttribute("width", QString::number(i->pen().width()));
                        writer.writeEndElement();
                        writer.writeTextElement("ShapeType", QString::number(i->type()));
                        writer.writeEndElement();
                        writer.writeEndDocument();
                    }
                }
            }
        }
    }
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Dialog"), currentDirOpen, tr("Files (*.xml)"));
    if(!fileName.isEmpty())
    {

    }
}

void MainWindow::hideTableList()
{
    ui->actionShow_List_View->setChecked(false);
    ui->action_Hide_List_View->setChecked(true);
    ui->dockWidget->hide();
}
