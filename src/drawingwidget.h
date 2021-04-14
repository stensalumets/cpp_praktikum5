#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>

class MainWindow;

enum STATE {
    NONE,
    ADD_VERTEX,
    MOVE_VERTEX,
    DELETE_VERTEX,
    ADD_LINE,
    DELETE_LINE
};
class DrawingWidget: public QWidget {
    Q_OBJECT
    public:
        DrawingWidget(MainWindow *parent = 0);
        ~DrawingWidget();

        STATE m_state = STATE::NONE;

        STATE getState() { return m_state; }
        void setState(STATE state);
    protected:
        void paintEvent(QPaintEvent *event);
        MainWindow *m_mainWindow;
};

#endif // DRAWINGWIDGET_H
