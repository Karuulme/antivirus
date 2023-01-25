#ifndef SCANRESULTOPERATIONS_H
#define SCANRESULTOPERATIONS_H

#include <QObject>
#include <QDebug>
class scanResultOperations : public QObject
{
    Q_OBJECT
public:
    explicit scanResultOperations(QObject *parent = nullptr);

private:
    void virusProcesses(QString path,int Options);
    void computerOperations(int Options);
signals:
public slots:
    void getApplyResults(QMap<int,QString> malwares,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions);
};
#endif // SCANRESULTOPERATIONS_H
