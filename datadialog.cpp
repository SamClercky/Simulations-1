#include "datadialog.h"
#include "ui_datadialog.h"
#include <QList>
#include <QDialog>

DataDialog::DataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataDialog)
{
    ui->setupUi(this);
}

DataDialog::~DataDialog()
{
    delete ui;
}

QList<int> DataDialog::getData() {
    QList<int> result;
    result.append(ui->aantalKeer->text().toInt());
    result.append(ui->aantalPers->text().toInt());
    result.append(ui->aantalKaart->text().toInt());

    return result;
}
