#ifndef RINGPROGRESSBAR_H
#define RINGPROGRESSBAR_H

#include <QWidget>
#include <QPainter>

class RingProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit RingProgressBar(QWidget *parent = nullptr);

    // Set the progress value (0-100)
    void setValue(int value);
    void setProgressColor(const QColor &color); // New method to set progress color

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_value;
    QColor m_progressColor; // Member variable to store the progress color
};

#endif // RINGPROGRESSBAR_H

