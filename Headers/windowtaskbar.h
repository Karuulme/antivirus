#ifndef WINDOWTASKBAR_H
#define WINDOWTASKBAR_H

#include <QObject>

class WindowTaskBar : public QObject
{
    Q_OBJECT
public:
    explicit WindowTaskBar(QObject *parent = nullptr);

signals:

public slots:
    void windowsClose();
};

#endif // WINDOWTASKBAR_H
