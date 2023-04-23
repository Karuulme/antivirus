
#ifndef CUSTOMFORM_H
#define CUSTOMFORM_H
#include <QtGui>

#include <QObject>
class customForm : public QWidget
{
public:
    customForm(QWidget *parent = 0) : customForm(parent) {}
protected:
    void mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPosition);
            event->accept();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            m_dragPosition = QPoint();
            event->accept();
        }
    }

private:
    QPoint m_dragPosition;
};
#endif // CUSTOMFORM_H
