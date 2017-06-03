#include "csvdata.h"
#include "ui_csvdata.h"
#include <QString>
#include <QList>

CsvData::CsvData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvData)
{
    ui->setupUi(this);
}

CsvData::~CsvData()
{
    delete ui;
}
void CsvData::setCsv(QString csv) {
    ui->CsvTxt->setText(csv);
}
void CsvData::setCsv(QList<QList<double>> csv) {
    // build the string
    QString result;

    for (QList<QList<double>>::iterator i = csv.begin(); i != csv.end(); ++i) {
        QList<double> temp = *i;
        for (QList<double>::iterator y = temp.begin(); y != temp.end(); ++y) {
            result.append(QString::number(*y));
            result.append(';');
        }
        result.append('\n');
    }

    setCsv(result);
}
