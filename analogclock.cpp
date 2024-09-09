#include "analogclock.h"
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QColor>

AnalogClock::AnalogClock(QWidget *parent)
    : QWidget(parent)
{

    // Set up a timer to update the clock every second
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);  // Start the timer with a 1000 ms interval

    setWindowTitle(tr("Feri Clock"));  // Set the window title
    resize(500, 500);  // Set the initial size of the window
}

AnalogClock::~AnalogClock() {}

void AnalogClock::paintEvent(QPaintEvent *event)
{
    static const QPoint hourHand[4] = {
        QPoint(5, 14),
        QPoint(-5, 14),
        QPoint(-4, -71),
        QPoint(4, -71)
    };

    static const QPoint minuteHand[4] = {
        QPoint(4, 14),
        QPoint(-4, 14),
        QPoint(-3, -89),
        QPoint(3, -89)
    };

    static const QPoint secondsHand[4] = {
        QPoint(1, 14),
        QPoint(-1, 14),
        QPoint(-1, -89),
        QPoint(1, -89)
    };

    const QColor hourColor(palette().color(QPalette::Text));  // Use the text color for hour hand
    const QColor minuteColor(palette().color(QPalette::Text)); // Use the text color for minute hand
    const QColor secondsColor(palette().color(QPalette::Accent)); // Use the accent color for seconds hand


    int side = qMin(width(), height());  // Determine the minimum side length

    QPainter painter(this);
    QTime time = QTime::currentTime();  // Get the current time

    painter.setRenderHint(QPainter::Antialiasing);  // Enable antialiasing for smoother graphics

    painter.translate(width() / 2, height() / 2);  // Move origin to center
    painter.scale(side / 200.0, side / 200.0);  // Scale based on the size of the widget

    // Draw the hour hand
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(30.0 * (time.hour() + time.minute() / 60.0));  // Calculate hour hand rotation
    painter.drawConvexPolygon(hourHand, 4);
    painter.restore();

    // Draw hour markers
    for (int i = 0; i < 12; ++i) {
        painter.drawRect(73, -3, 16, 6); // Draw rectangular hour markers
        painter.rotate(30.0);  // Rotate for next marker
    }

    // Draw the minute hand
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0 * time.minute());  // Calculate minute hand rotation
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();

    // Draw the second hand
    painter.setBrush(secondsColor);
    painter.save();
    painter.rotate(6.0 * time.second());  // Calculate second hand rotation
    painter.drawConvexPolygon(secondsHand, 4);
    painter.drawEllipse(-3, -3, 6, 6);  // Draw the tip of the second hand
    painter.drawEllipse(-5, -68, 10, 10);  // Draw the center circle for second hand
    painter.restore();

    // Draw minute markers
    painter.setPen(minuteColor);
    for (int j = 0; j < 60; ++j) {
        painter.drawLine(92, 0, 96, 0);  // Draw minute markers
        painter.rotate(6.0);  // Rotate for the next marker
    }
}


