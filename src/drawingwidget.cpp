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
}
