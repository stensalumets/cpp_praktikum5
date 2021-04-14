#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class DrawingWidget;
class QMenu;

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    protected:
        void initMenus();
        void initWidgets();

        DrawingWidget *m_drawingWidget;

        QMenu *m_fileMenu;
            QAction *m_quitAction;
        QMenu *m_helpMenu;
            QAction *m_whatsThisAction;
            QAction *m_aboutAction;
};

#endif // MAINWINDOW_H
