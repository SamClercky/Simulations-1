#ifndef GENERATEDATA_H
#define GENERATEDATA_H

#include <stdlib.h>
#include <QList>

class GenerateData
{
public:
    GenerateData(int aantalKeer = 0, int aantalPersonen = 0, int aantalKaarten = 0);
    QVector<QVector<int>> Generate();

private:
    int aantalKeer = 0;
    int aantalPersonen = 0;
    int aantalKaarten = 0;

    int OnePerson();
    int GenerateRandom(int max = RAND_MAX);
    QVector<int> prepare(QVector<int> v);
};

#endif // GENERATEDATA_H
