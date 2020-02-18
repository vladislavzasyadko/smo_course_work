#include "resultswindow.h"
#include "ui_resultswindow.h"
#include "stepmode.h"
#include "QStandardItemModel"
#include "QStandardItem"

ResultsWindow::ResultsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultsWindow)
{
    ui->setupUi(this);
}

void ResultsWindow::init(Results data){
    this->data = data;
    createMainTable();
    createDeviceTable();
}

void ResultsWindow::initSteps(Step steps)
{
    std::cout << "initi steps" << std::endl;
    this->steps = steps;
}

ResultsWindow::~ResultsWindow()
{
    delete ui;
}

void ResultsWindow::createMainTable(){
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Req. proc");
    horizontalHeader.append("Req. failed");
    horizontalHeader.append("Time in system");
    horizontalHeader.append("Time of wait");
    horizontalHeader.append("Time of process");
    horizontalHeader.append("Prob. of fail");
    horizontalHeader.append("Disp of wait");
    horizontalHeader.append("Disp of proc");

    //Заголовки строк
    QStringList verticalHeader;
    for(int i = 1; i <= this->data.numberOfGenerators; i++){
        QString header = "Generator ";
        header.append(QString::number(i));
        verticalHeader.append(header);
    }


    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    for(int i = 0; i < this->data.numberOfGenerators; i++){
            item = new QStandardItem(QString::number(this->data.processed[i]));
            item->setEditable(false);
            model->setItem(i, 0, item);
            item = new QStandardItem(QString::number(this->data.failed[i]));
            item->setEditable(false);
            model->setItem(i, 1, item);
            item = new QStandardItem(QString::number(this->data.waitTimes[i]+this->data.processTimes[i]));
            item->setEditable(false);
            model->setItem(i, 2, item);
            item = new QStandardItem(QString::number(this->data.waitTimes[i]));
            item->setEditable(false);
            model->setItem(i, 3, item);
            item = new QStandardItem(QString::number(this->data.processTimes[i]));
            item->setEditable(false);
            model->setItem(i, 4, item);
            item = new QStandardItem(QString::number(this->data.failureProb[i]));
            item->setEditable(false);
            model->setItem(i, 5, item);
            item = new QStandardItem(QString::number(this->data.dispOfWait[i]));
            item->setEditable(false);
            model->setItem(i, 6, item);
            item = new QStandardItem(QString::number(this->data.dispOfProc[i]));
            item->setEditable(false);
            model->setItem(i, 7, item);
    }


    ui->tableView->setModel(model);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void ResultsWindow::createDeviceTable(){
    QStandardItemModel *devices = new QStandardItemModel;
    QStandardItem *item;
    //Заголовки столбцов
    QStringList devicehorizontalHeader;
    devicehorizontalHeader.append("Device Occupation");

    //Заголовки строк
    QStringList deviceverticalHeader;
    for(int i = 1; i <= this->data.numberOfDevices; i++){
        QString devheader = "Device ";
        devheader.append(QString::number(i));
        deviceverticalHeader.append(devheader);
    }


    devices->setHorizontalHeaderLabels(devicehorizontalHeader);
    devices->setVerticalHeaderLabels(deviceverticalHeader);

    for(int i = 0; i < this->data.numberOfDevices; i++){
            item = new QStandardItem(QString::number(this->data.deviceBusy[i]));
            item->setEditable(false);
            devices->setItem(i, 0, item);
    }


    ui->deviceTable->setModel(devices);

    ui->deviceTable->resizeRowsToContents();
    ui->deviceTable->resizeColumnsToContents();
}

void ResultsWindow::on_StepMode_clicked()
{
    StepMode *step = new StepMode();
    step->init(data.numberOfGenerators, data.bufferSize, data.numberOfDevices, this->steps);
    step->move( 600, 250 );
    step->show();
}
