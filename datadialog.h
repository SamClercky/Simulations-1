#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QDialog>
#include <QList>

namespace Ui {
class DataDialog;
}

class DataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialog(QWidget *parent = 0);
    QList<int> getData();
    ~DataDialog();

private:
    Ui::DataDialog *ui;
};

#endif // DATADIALOG_H
