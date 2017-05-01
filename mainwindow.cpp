#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generatedata.h"
#include "getdatainthread.h"
#include <QList>
#include <QVector>
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    if (
            isInputValid(ui->aantalKeer->text().toInt()) &&
            isInputValid(ui->aantalPers->text().toInt()) &&
            isInputValid(ui->aantalKaart->text().toInt())) {
        auto *customPlot = ui->Chart;
        // remove all plots
        for(int i = 0; i < customPlot->graphCount(); i++) {
            customPlot->removeGraph(i);
        }
        this->GraphId = 0;
        customPlot->xAxis->setLabel("#personen");
        customPlot->yAxis->setLabel("#kaarten");

        ui->pushButton->setEnabled(false);
        ui->aantalKaart->setEnabled(false);
        ui->aantalKeer->setEnabled(false);
        ui->aantalPers->setEnabled(false);

        ui->status->setText("Processing...");
        qDebug("emiting");
        emit MainWindow::StartGettingData(
                    ui->aantalKeer->text().toInt(),
                    ui->aantalPers->text().toInt(),
                    ui->aantalKaart->text().toInt()
         );
        qDebug("emited");
    } else {
        ui->status->setText("Invalid input: input must be bigger than 0");
    }
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
}
void MainWindow::DataReady() {
    ui->pushButton->setEnabled(true);
    ui->aantalKaart->setEnabled(true);
    ui->aantalKeer->setEnabled(true);
    ui->aantalPers->setEnabled(true);

    ui->status->setText("Ready to simulate");
}
bool MainWindow::isInputValid(int check) {
    return check > 0;
}
