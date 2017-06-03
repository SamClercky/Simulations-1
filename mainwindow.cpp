#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generatedata.h"
#include "getdatainthread.h"
#include "datadialog.h"
#include "csvdata.h"
#include <QList>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <QDialog>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setVisible(false);
    ui->GetCsvBtn->setEnabled(false);

    // thread
    GetDataInThread *thread = new GetDataInThread();
    thread->moveToThread(&workerThread);
    connect(this, &MainWindow::StartGettingData, thread, &GetDataInThread::StartGettingData);
    connect(thread, &GetDataInThread::GotPoints, this, &MainWindow::GotGraphPoints);
    connect(thread, &GetDataInThread::GotMax, this, &MainWindow::GotMax);
    connect(&workerThread, &QThread::finished, thread, &GetDataInThread::deleteLater);
    connect(thread, &GetDataInThread::DataReady, this, &MainWindow::DataReady);
    workerThread.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::on_pushButton_clicked()
{
    DataDialog *d = new DataDialog(this);
    if (d->exec() == QDialog::Accepted) {
        QList<int> data = d->getData();

        if (
                isInputValid(data[0]) &&
                isInputValid(data[1]) &&
                isInputValid(data[2])) {
            auto *customPlot = ui->Chart;
            aantalOntvangen = 0;
            aantalVerzonden = 0;
            for(int i = 0; i < customPlot->graphCount(); i++) {
                customPlot->removeGraph(i);
            }
            this->GraphId = 0;
            customPlot->xAxis->setLabel("#personen");
            customPlot->yAxis->setLabel("#kaarten");

            ui->pushButton->setEnabled(false);
            ui->GetCsvBtn->setEnabled(false);

            qDebug() << "<======================================================>";

            ui->status->setText("Processing...");
            for(int i = 0; i < data[0]; i++) {
                aantalVerzonden++;
                emit MainWindow::StartGettingData(
                            1,
                            data[1],
                            data[2]
                );
            }
        } else {
            ui->status->setText("Invalid input: input must be bigger than 0");
        }
    }
    delete d;
}
void MainWindow::GotMax(double maxx, double maxy) {
    auto *customPlot = ui->Chart;
    customPlot->xAxis->setRange(0, maxx*1.2);
    customPlot->yAxis->setRange(0, maxy*1.2);
    customPlot->replot();
}
void MainWindow::GotGraphPoints(QVector<double> x, QVector<double> y) {
    int id = this->GraphId;
    this->GraphId++;

    auto *customPlot = ui->Chart;
    customPlot->addGraph();
    customPlot->graph(id)->setData(x, y);
    customPlot->replot();

    // add to carts
    carts.append(y.toList());
}
void MainWindow::DataReady(int teProducerenKaarten) {
    ui->progressBar->setVisible(true);
    aantalOntvangen++;

    if (aantalOntvangen == aantalVerzonden) {
        ui->pushButton->setEnabled(true);
        ui->GetCsvBtn->setEnabled(true);
        ui->status->setText("Mediaan te produceren kaarten: " + QString::number(calcMedian(distributedCarts)));
    } else {
        distributedCarts.append(teProducerenKaarten);
    }

    qDebug() << "Te produceren kaarten: " << teProducerenKaarten;
    ui->progressBar->setValue(calcProCent(aantalOntvangen));
}
bool MainWindow::isInputValid(int check) {
    return check > 0;
}
int MainWindow::calcProCent(int toCent) {
    int result = toCent * 100;
    result /= aantalVerzonden;
    if (result > 100) {
        result = 100;
    }

    return result;
}
int MainWindow::calcMedian(QList<int> lijst) {
    return lijst[qFloor(lijst.count() / 2)];
}

void MainWindow::on_GetCsvBtn_clicked()
{
    CsvData csvData(this);
    csvData.setCsv(carts);
    csvData.exec();
}
