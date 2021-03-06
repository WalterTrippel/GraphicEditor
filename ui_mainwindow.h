/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionHideDrawingTools;
    QAction *actionCloseTab;
    QAction *actionShow_List_View;
    QAction *action_Hide_List_View;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menu_Show_Drawing_Tools;
    QStatusBar *statusBar;
    QDockWidget *drawingTools;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QPushButton *bFill;
    QPushButton *bDrawLine;
    QPushButton *bDrawRectangle;
    QPushButton *bDrawEllipse;
    QPushButton *bTriangle;
    QFrame *line;
    QPushButton *bPenColor;
    QPushButton *bPenWidth;
    QRadioButton *rShowName;
    QRadioButton *rHideName;
    QSpacerItem *verticalSpacer;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(778, 383);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionHideDrawingTools = new QAction(MainWindow);
        actionHideDrawingTools->setObjectName(QStringLiteral("actionHideDrawingTools"));
        actionCloseTab = new QAction(MainWindow);
        actionCloseTab->setObjectName(QStringLiteral("actionCloseTab"));
        actionShow_List_View = new QAction(MainWindow);
        actionShow_List_View->setObjectName(QStringLiteral("actionShow_List_View"));
        action_Hide_List_View = new QAction(MainWindow);
        action_Hide_List_View->setObjectName(QStringLiteral("action_Hide_List_View"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(false);
        centralWidget->setAutoFillBackground(false);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setCursor(QCursor(Qt::CrossCursor));
        tabWidget->setMouseTracking(false);
        tabWidget->setStyleSheet(QStringLiteral("QWidget { background-color: lightGray; }"));
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 778, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menu_Show_Drawing_Tools = new QMenu(menuView);
        menu_Show_Drawing_Tools->setObjectName(QStringLiteral("menu_Show_Drawing_Tools"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        drawingTools = new QDockWidget(MainWindow);
        drawingTools->setObjectName(QStringLiteral("drawingTools"));
        drawingTools->setCursor(QCursor(Qt::ArrowCursor));
        drawingTools->setFeatures(QDockWidget::DockWidgetFeatureMask);
        drawingTools->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidgetContents_2->setLayoutDirection(Qt::LeftToRight);
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        bFill = new QPushButton(dockWidgetContents_2);
        bFill->setObjectName(QStringLiteral("bFill"));

        verticalLayout->addWidget(bFill);

        bDrawLine = new QPushButton(dockWidgetContents_2);
        bDrawLine->setObjectName(QStringLiteral("bDrawLine"));
        bDrawLine->setCheckable(true);

        verticalLayout->addWidget(bDrawLine);

        bDrawRectangle = new QPushButton(dockWidgetContents_2);
        bDrawRectangle->setObjectName(QStringLiteral("bDrawRectangle"));
        bDrawRectangle->setCheckable(true);

        verticalLayout->addWidget(bDrawRectangle);

        bDrawEllipse = new QPushButton(dockWidgetContents_2);
        bDrawEllipse->setObjectName(QStringLiteral("bDrawEllipse"));
        bDrawEllipse->setCheckable(true);

        verticalLayout->addWidget(bDrawEllipse);

        bTriangle = new QPushButton(dockWidgetContents_2);
        bTriangle->setObjectName(QStringLiteral("bTriangle"));

        verticalLayout->addWidget(bTriangle);

        line = new QFrame(dockWidgetContents_2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        bPenColor = new QPushButton(dockWidgetContents_2);
        bPenColor->setObjectName(QStringLiteral("bPenColor"));

        verticalLayout->addWidget(bPenColor);

        bPenWidth = new QPushButton(dockWidgetContents_2);
        bPenWidth->setObjectName(QStringLiteral("bPenWidth"));

        verticalLayout->addWidget(bPenWidth);

        rShowName = new QRadioButton(dockWidgetContents_2);
        rShowName->setObjectName(QStringLiteral("rShowName"));

        verticalLayout->addWidget(rShowName);

        rHideName = new QRadioButton(dockWidgetContents_2);
        rHideName->setObjectName(QStringLiteral("rHideName"));
        rHideName->setChecked(true);

        verticalLayout->addWidget(rHideName);

        verticalSpacer = new QSpacerItem(20, 94, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        drawingTools->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), drawingTools);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        listWidget = new QListWidget(dockWidgetContents);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 251, 311));
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionCloseTab);
        menuFile->addAction(actionExit);
        menuView->addAction(menu_Show_Drawing_Tools->menuAction());
        menuView->addAction(actionHideDrawingTools);
        menuView->addAction(actionShow_List_View);
        menuView->addAction(action_Hide_List_View);

        retranslateUi(MainWindow);
        QObject::connect(actionHideDrawingTools, SIGNAL(triggered()), drawingTools, SLOT(hide()));
        QObject::connect(drawingTools, SIGNAL(visibilityChanged(bool)), actionHideDrawingTools, SLOT(setEnabled(bool)));
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(newImage()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(open()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(save()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionCloseTab, SIGNAL(triggered()), MainWindow, SLOT(closeTab()));
        QObject::connect(tabWidget, SIGNAL(tabCloseRequested(int)), MainWindow, SLOT(closeTab(int)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GraphicEditor", 0));
        actionNew->setText(QApplication::translate("MainWindow", "&New", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionHideDrawingTools->setText(QApplication::translate("MainWindow", "&Hide Drawing Tools", 0));
        actionCloseTab->setText(QApplication::translate("MainWindow", "&Close Tab", 0));
        actionCloseTab->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0));
        actionShow_List_View->setText(QApplication::translate("MainWindow", "Show &List View", 0));
        action_Hide_List_View->setText(QApplication::translate("MainWindow", "Hide List &View", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "New", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fi&le", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0));
        menu_Show_Drawing_Tools->setTitle(QApplication::translate("MainWindow", "&Show Drawing Tools", 0));
#ifndef QT_NO_TOOLTIP
        drawingTools->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Drawing Tools</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        drawingTools->setWindowTitle(QApplication::translate("MainWindow", "D&rawing Tools", 0));
        bFill->setText(QApplication::translate("MainWindow", "Fill", 0));
#ifndef QT_NO_TOOLTIP
        bDrawLine->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Draw Line</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        bDrawLine->setText(QApplication::translate("MainWindow", "Line", 0));
#ifndef QT_NO_TOOLTIP
        bDrawRectangle->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Draw Rectangle</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        bDrawRectangle->setText(QApplication::translate("MainWindow", "Rectangle", 0));
#ifndef QT_NO_TOOLTIP
        bDrawEllipse->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Draw Ellipse</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        bDrawEllipse->setText(QApplication::translate("MainWindow", "Ellipse", 0));
        bTriangle->setText(QApplication::translate("MainWindow", "Triangle", 0));
#ifndef QT_NO_TOOLTIP
        bPenColor->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Set Pen Color</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        bPenColor->setText(QApplication::translate("MainWindow", "Pen Color", 0));
#ifndef QT_NO_TOOLTIP
        bPenWidth->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Set Pen Width</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        bPenWidth->setText(QApplication::translate("MainWindow", "Pen Width", 0));
        rShowName->setText(QApplication::translate("MainWindow", "Show Na&me", 0));
        rHideName->setText(QApplication::translate("MainWindow", "&Hide Name", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
