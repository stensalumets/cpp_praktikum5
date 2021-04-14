#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class DrawingWidget;
class QMenu;

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

        QLabel *m_vertexCount;
        QLabel *m_lineCount;
    public slots:
        void addVertices();
        void moveVertices();
        void deleteVertices();
        void addLine();
        void deleteLine();
    protected:
        void initMenus();
        void initWidgets();
        void initStatusBar();

        DrawingWidget *m_drawingWidget;

        QMenu *m_fileMenu;
            QAction *m_quitAction;
        QMenu *m_helpMenu;
            QAction *m_whatsThisAction;
            QAction *m_aboutAction;
        QMenu *m_toolsMenu;
            QAction *m_AddVertexAction;
            QAction *m_MoveVertexAction;
            QAction *m_DeleteVertexAction;
            QAction *m_AddLineAction;
            QAction *m_DeleteLineAction;
        QStatusBar *m_statusBar;
            QLabel *m_activeTool;

};

#endif // MAINWINDOW_H
