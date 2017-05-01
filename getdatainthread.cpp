#include "getdatainthread.h"
#include "generatedata.h"
#include <QDebug>
#include <QVector>

GetDataInThread::GetDataInThread() {
    qRegisterMetaType<QVector<double>>("QVector<double>");
}

void GetDataInThread::StartGettingData(int aantalKeer, int aantalPers, int aantalKaart) {
    GenerateData generator(
                aantalKeer,
                aantalPers,
                aantalKaart
     );

    QVector<QVector<int>> data = generator.Generate();
    qDebug() << data;
    double maxy = 1;
    double maxx = 1;
    for (int i = 0; i < data.count(); i++) {
        QVector<double> x(data[i].count()), y(data[i].count());
        for (int d = 0; d < data.at(i).count(); d++) {
            x[d] = d;
            y[d] = data.at(i).at(d);
            maxy = qMax(maxy, y[d]);
            maxx = qMax(maxx, x[d]);
            qDebug() << "x: " << x[d] << ", y: " << y[d];
        }
        emit this->GotPoints(x, y);
    }
    emit this->GotMax(maxx, maxy);
    emit this->DataReady();
}
