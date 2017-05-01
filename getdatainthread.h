#ifndef GETDATAINTHREAD_H
#define GETDATAINTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>

class GetDataInThread : public QObject
{
    Q_OBJECT

public:
    GetDataInThread();

public slots:
    void StartGettingData(int aantalKeer, int aantalPers, int aantalKaart);

signals:
    void GotPoints(const QVector<double> x, const QVector<double> y);
    void GotMax(const double maxx, const double maxy);
    void DataReady(int teProducerenKaarten);
};

#endif // GETDATAINTHREAD_H
