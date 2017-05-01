#include <qglobal.h>
#include <stdlib.h>
#include <QVector>
#include <QList>
#include <QDebug>
#include "generatedata.h"

GenerateData::GenerateData(int aantalKeer, int aantalPersonen, int aantalKaarten)
{
    this->aantalKeer = aantalKeer;
    this->aantalPersonen = aantalPersonen;
    this->aantalKaarten = aantalKaarten;
    this->teProducerenKaarten = 0;

    qDebug() << "Init GenerateData: aantalKeer: " << this->aantalKeer
             << " AantalPersonen: " << this->aantalPersonen
             << " AantalKaarten: " << this->aantalKaarten;
}
int GenerateData::OnePerson()
{
    int i = 0;
    int aantal = 0;
    while(i <= this->aantalKaarten) {
        int janee = this->GenerateRandom(2);
        qDebug() << janee;
        if(janee == 2) janee = 1;

        if (janee == 1) {
            i++;
        }
        this->teProducerenKaarten++;
        aantal++;
    }
    qDebug() << aantal;
    return aantal;
}
QVector<QVector<int>> GenerateData::Generate()
{
    QList<QVector<int>> result;
    for(int i = 0; i < this->aantalKeer; i++) {
        QList<int> keer;
        for(int y = 0; y < this->aantalPersonen; y++) {
            keer.append(this->OnePerson());
        }
        result.append(this->prepare(keer.toVector()));
    }
    return result.toVector();
}
QVector<int> GenerateData::prepare(QVector<int> v)
{
    QVector<int> result = v;
    qSort(result);

    return result;
}
int GenerateData::GenerateRandom(int max)
{
    qDebug() << "RAND_MAX: " << RAND_MAX;
    double result = qrand();
    qDebug() << result;
    result *= max;
    result /= RAND_MAX;
    return result;
}
int GenerateData::getTeProducerenKaarten() {
    return this->teProducerenKaarten;
}

