#ifndef CSVDATA_H
#define CSVDATA_H

#include <QDialog>
#include <QString>
#include <QList>

namespace Ui {
class CsvData;
}

class CsvData : public QDialog
{
    Q_OBJECT

public:
    explicit CsvData(QWidget *parent = 0);
    ~CsvData();
    void setCsv(QString csv);
    void setCsv(QList<QList<double>> csv);

private:
    Ui::CsvData *ui;
};

#endif // CSVDATA_H
