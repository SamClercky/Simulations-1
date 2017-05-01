#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "getdatainthread.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void StartGettingData(int aantalKeer, int aantalPers, int aantalKaart);

public slots:
    void GotGraphPoints(QVector<double> x, QVector<double> y);
    void GotMax(double maxx, double maxy);
    void DataReady();

private slots:
    void on_pushButton_clicked();

private:
    bool isInputValid(int check);
    QThread workerThread;
    Ui::MainWindow *ui;
    int GraphId = 0;
};

#endif // MAINWINDOW_H
