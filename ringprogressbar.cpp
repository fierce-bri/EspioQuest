#include "ringprogressbar.h"

RingProgressBar::RingProgressBar(QWidget *parent) : QWidget(parent), m_value(0)
{
    setFixedSize(100, 100); // Set a fixed size for the ring progress bar
    m_progressColor = Qt::green; // Default progress color
}

void RingProgressBar::setValue(int value)
{
    // Ensure the value is within the range 0-100
    m_value = qBound(0, value, 100);
    update(); // Update the widget to trigger repainting
}

void RingProgressBar::setProgressColor(const QColor &color)
{
    m_progressColor = color; // Set the new progress color
    update(); // Update the widget to trigger repainting with the new color
}

void RingProgressBar::paintEvent(QPaintEvent *event)
{
    // Draw the ring based on the current value
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF outerRect = rect().adjusted(5, 5, -5, -5); // Adjust the rectangle to create an outer ring

    // Calculate the angle based on the current value (clockwise direction)
    int angle = 360 - (360 * m_value / 100);

    // Draw the outer ring with the progress color
    painter.setPen(QPen(m_progressColor, 5)); // Set pen color and width
    painter.drawArc(outerRect, 90 * 16, -angle * 16); // Draw a clockwise arc
}


