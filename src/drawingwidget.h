#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include "point2.h"
#include "line2.h"

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

        QList<Point2> m_vertices;
        QList<Line2> m_lines;

        int index_of_movable_vertex = -1;
        bool onePointSelected = false;
        Point2 firstPoint;

        Point2 getClosestPoint(int x, int y);

        STATE m_state = STATE::NONE;

        STATE getState() { return m_state; }
        void setState(STATE state);
    protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        MainWindow *m_mainWindow;
};

#endif // DRAWINGWIDGET_H
