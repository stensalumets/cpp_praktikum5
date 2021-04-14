#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QEvent>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QWhatsThis>
#include "drawingwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	initWidgets();
    initMenus();
}

MainWindow::~MainWindow() {
    // Intentionally empty
}

/**
  Initializes all menus of this widget.
*/
void MainWindow::initMenus() {
    // Creates the file menu
    m_fileMenu = new QMenu(this);
    m_fileMenu->setTitle(QString("&File"));
    menuBar()->addMenu(m_fileMenu);

    // Creates the quit action in the file menu
    m_quitAction = new QAction(this);
    m_quitAction->setMenuRole(QAction::QuitRole);
    m_quitAction->setText(QString("&Quit"));
    m_quitAction->setStatusTip(QString("Quits this application"));
    m_quitAction->setToolTip(QString("Quits this application"));
    m_quitAction->setWhatsThis(QString("Activate this item to quit this application. You will"
                                  " be asked for confirmation."));
    m_fileMenu->addAction(m_quitAction);

    // Connects the triggering of the quit action
    // to closing the main window
    connect(m_quitAction, SIGNAL(triggered()),
            this, SLOT(close()));    
    
    // Create the help menu and its contents
    m_helpMenu = new QMenu(this);
    m_helpMenu->setTitle(QString("&Help"));
    menuBar()->addMenu(m_helpMenu);

    m_whatsThisAction = QWhatsThis::createAction(this);
    m_whatsThisAction->setText(QString("&Whats this?"));
    m_helpMenu->addAction(m_whatsThisAction);

    m_aboutAction = new QAction(this);
    m_aboutAction->setMenuRole(QAction::AboutQtRole);
    m_aboutAction->setText(QString("&About"));
    m_helpMenu->addAction(m_aboutAction);
    connect(m_aboutAction, SIGNAL(triggered()),
            qApp, SLOT(aboutQt()));

}

/**
  Translates all texts of this widget.
*/
void MainWindow::initWidgets() {
    setWindowTitle(QString("Drawing"));

    m_drawingWidget = new DrawingWidget(this);
    setCentralWidget(m_drawingWidget);
}

