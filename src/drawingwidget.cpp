#include "drawingwidget.h"

#include <QPainter>
#include <QPaintEvent>
#include "mainwindow.h"

/**
  Constructs a drawing widget.
  \param[in] parent parent widget of the drawing widget.
*/
DrawingWidget::DrawingWidget(MainWindow *parent)
    : QWidget(parent), m_mainWindow(parent)
{
    // Nothing here yet
}

DrawingWidget::~DrawingWidget() {
    // Nothing here yet
}

void DrawingWidget::setState(STATE state) {
    m_state = state;
}

/**
  Overridden method to handle all received paint events.
  \param[in] event the paint event that was received.
*/
void DrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    const QColor myColor(143,188,143, 255);
    painter.fillRect(event->rect(), myColor);

    if(!m_vertices.isEmpty()) {
        painter.setBrush(Qt::black);
        QListIterator<Point2> iteraator(m_vertices);
        while(iteraator.hasNext()) {
            Point2 punkt = iteraator.next();
            painter.drawEllipse(punkt.x, punkt.y, 20, 20);
        }
    }

    if(!m_lines.isEmpty()) {
        painter.setBrush(Qt::black);
        QListIterator<Line2> iteraator(m_lines);
        while(iteraator.hasNext()) {
            Line2 loik = iteraator.next();
            painter.drawLine(loik.p1.x + 10, loik.p1.y + 10, loik.p2.x + 10, loik.p2.y + 10);
        }
    }

}

void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    int m_x = event->x() - 10;
    int m_y = event->y() - 10;

    if (m_state == STATE::ADD_VERTEX) {
        Point2 uus_punkt = Point2(m_x, m_y);
        // check if there's a point in 10px radius
        bool canBeDrawn = true;
        QListIterator<Point2> iteraator(m_vertices);
        while(iteraator.hasNext()) {
            Point2 punkt = iteraator.next();
            if (uus_punkt.distanceFrom(punkt) <= 10) {
                canBeDrawn = false;
            }
        }
        if (canBeDrawn) { m_vertices.append(uus_punkt); }
        update(); //Canvas on muutunud
    }

    if (m_state == STATE::MOVE_VERTEX) {
        Point2 closest_punkt = getClosestPoint(m_x, m_y);
        if (closest_punkt.distanceFrom(Point2(m_x, m_y)) <= 10 && m_vertices.contains(closest_punkt)) { //kas vajutati ikka punkti peale
            index_of_movable_vertex = m_vertices.indexOf(closest_punkt);

        }
    }

    if (m_state == STATE::DELETE_VERTEX) {
        Point2 closest_punkt = getClosestPoint(m_x, m_y);
        if (closest_punkt.distanceFrom(Point2(m_x, m_y)) <= 10 && m_vertices.contains(closest_punkt)) { //kas vajutati ikka punkti peale
            m_vertices.removeAt(m_vertices.indexOf(closest_punkt));

            if(!m_lines.isEmpty()) {  // Kontrolli kas punktiga oli mõni lõik seotud
                QListIterator<Line2> iteraator(m_lines);
                while(iteraator.hasNext()) {
                    Line2 loik = iteraator.next();
                    if (loik.p1 == closest_punkt || loik.p2 == closest_punkt) {
                        m_lines.removeAt(m_lines.indexOf(loik)); // eemalda, kui on
                    }
                }
            }

            update(); //Canvas on muutunud
        }
    }

    if (m_state == STATE::ADD_LINE) {
        Point2 closest_punkt = getClosestPoint(m_x, m_y);
        if (closest_punkt.distanceFrom(Point2(m_x, m_y)) <= 10 && m_vertices.contains(closest_punkt)) { //kas vajutati ikka punkti peale
            if (!onePointSelected) { // esimese punkti valimine
                firstPoint = closest_punkt;
                onePointSelected = true;
            } else { // teise punkti valimine ja lisamine listi, kui seda seal veel ei ole
                Line2 lisatav = Line2(firstPoint, closest_punkt);
                if (!m_lines.contains(lisatav)) {
                    m_lines.append(Line2(firstPoint, closest_punkt));
                }
                onePointSelected = false;
                update();
            }
        }
    }

    if (m_state == STATE::DELETE_LINE) {

    }
    std::cout << "Mouse press: " << m_x << " " << m_y << std::endl;
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if (m_state == STATE::MOVE_VERTEX) {
        if (index_of_movable_vertex != -1 ) {
            int m_x = event->x() - 10;
            int m_y = event->y() - 10;

            if (m_x < 0) { m_x = 0; }
            if (m_x > 780) { m_x = 780; }
            if (m_y < 0) { m_y = 0; }
            if (m_y > 535) { m_y = 535; }

            Point2 liigutatav = m_vertices[index_of_movable_vertex];

            if(!m_lines.isEmpty()) {  // Kontrolli kas punktiga oli mõni lõik seotud
                QListIterator<Line2> iteraator(m_lines);
                while(iteraator.hasNext()) {
                    Line2 loik = iteraator.next();
                    if (loik.p1 == liigutatav) { //Kui on, siis liiguta lõiku ka
                        m_lines.removeAt(m_lines.indexOf(loik));
                        loik.p1.x = m_x;
                        loik.p1.y = m_y;
                        m_lines.append(loik);
                    }
                    if (loik.p2 == liigutatav) {
                        m_lines.removeAt(m_lines.indexOf(loik));
                        loik.p2.x = m_x;
                        loik.p2.y = m_y;
                        m_lines.append(loik);
                    }
                }
            }

            m_vertices[index_of_movable_vertex].x = m_x;
            m_vertices[index_of_movable_vertex].y = m_y;

            update(); //Canvas on muutunud
        }
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (m_state == STATE::MOVE_VERTEX) {
        index_of_movable_vertex = -1;
    }
}

Point2 DrawingWidget::getClosestPoint(int x, int y) {
    if (!m_vertices.isEmpty()) {
        Point2 vajutus = Point2(x, y);
        int kaugus = 1000000; // piisavalt suur arv, et sellest oleks kõik punktid lähemal
        Point2 punkt;
        QListIterator<Point2> iteraator(m_vertices); //vaata kõik punktid läbi, otsi vajutusele lähim
        while(iteraator.hasNext()) {
            Point2 uus_punkt = iteraator.next();
            if (uus_punkt.distanceFrom(vajutus) < kaugus) {
                punkt = uus_punkt;
                kaugus = uus_punkt.distanceFrom(vajutus);
            }
        }
        return punkt;
    }
}
