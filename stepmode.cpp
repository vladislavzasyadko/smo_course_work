#include "stepmode.h"
#include "ui_stepmode.h"
//#include "qcustomplot.h"


#include <QStandardItem>
#include <QVBoxLayout>
#include <qpushbutton.h>

StepMode::StepMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepMode)
{
    ui->setupUi(this);
}

StepMode::~StepMode()
{
    delete ui;
}

void StepMode::init(int numberOfGenerators, int bufferSize, int numberOfDevices, Step& steps){
    this->numberOfGenerators = numberOfGenerators;
    this->numberOfDevices = numberOfDevices;
    this->bufferSize = bufferSize;
    this->steps = steps;
    std::cout << steps.getGenState() << std::endl;
    this->currentIndex = 0;
    this->phase = 0;
}

void StepMode::createGeneratorTable()
{
    QStandardItemModel *generator = new QStandardItemModel;
    QStandardItem *item;
    //Заголовки столбцов
    QStringList genhorizontalHeader;
    genhorizontalHeader.append(" ");

    //Заголовки строк
    QStringList genverticalHeader;
    for(int i = 1; i <= numberOfGenerators; i++){
        QString genheader = "Generator ";
        genheader.append(QString::number(i));
        genverticalHeader.append(genheader);
    }


    generator->setHorizontalHeaderLabels(genhorizontalHeader);
    generator->setVerticalHeaderLabels(genverticalHeader);
    std::vector<std::string> result;
    boost::split(result, steps.getGenState(), boost::is_any_of(" "));
    for(int i = 0; i < numberOfGenerators; i++){
            if(result[0] == std::to_string(i+1)){
                item = new QStandardItem(result[1].c_str());//steps.getGenState().c_str()
            }else{
                item = new QStandardItem();

            }
            item->setEditable(false);
            generator->setItem(i, 0, item);
    }


    ui->GeneratorTable->setModel(generator);

    ui->GeneratorTable->resizeRowsToContents();
    ui->GeneratorTable->resizeColumnsToContents();
}

void StepMode::createBufferTable()
{
    QStandardItemModel *buffer = new QStandardItemModel;
    QStandardItem *item;
    //Заголовки столбцов
    QStringList bufferhorizontalHeader;
    bufferhorizontalHeader.append(" ");

    //Заголовки строк
    QStringList bufferverticalHeader;
    for(int i = 1; i <= steps.getBufferState().size(); i++){
        QString bufferheader = "Buffer ";
        bufferheader.append(QString::number(i));
        bufferverticalHeader.append(bufferheader);
    }


    buffer->setHorizontalHeaderLabels(bufferhorizontalHeader);
    buffer->setVerticalHeaderLabels(bufferverticalHeader);
    std::cout << steps.getBufferState().size() <<std::endl;
    for(int i = 0; i < steps.getBufferState().size(); i++){
        std::cout << steps.getBufferState()[i];
            item = new QStandardItem((steps.getBufferState()[i]).c_str());
            item->setEditable(false);
            buffer->setItem(i, 0, item);
    }


    ui->BufferTable->setModel(buffer);

    ui->BufferTable->resizeRowsToContents();
    ui->BufferTable->resizeColumnsToContents();
}

void StepMode::createBufferAfterTable()
{
    QStandardItemModel *buffer = new QStandardItemModel;
    QStandardItem *item;
    //Заголовки столбцов
    QStringList bufferhorizontalHeader;
    bufferhorizontalHeader.append(" ");

    //Заголовки строк
    QStringList bufferverticalHeader;
    for(int i = 1; i <= steps.getBufferAfterState().size(); i++){
        QString bufferheader = "Buffer ";
        bufferheader.append(QString::number(i));
        bufferverticalHeader.append(bufferheader);
    }


    buffer->setHorizontalHeaderLabels(bufferhorizontalHeader);
    buffer->setVerticalHeaderLabels(bufferverticalHeader);
    std::cout << steps.getBufferAfterState().size() <<std::endl;
    for(int i = 0; i < steps.getBufferAfterState().size(); i++){
        std::cout << steps.getBufferAfterState()[i];
            item = new QStandardItem((steps.getBufferAfterState()[i]).c_str());
            item->setEditable(false);
            buffer->setItem(i, 0, item);
    }


    ui->BufferTable->setModel(buffer);

    ui->BufferTable->resizeRowsToContents();
    ui->BufferTable->resizeColumnsToContents();
}

void StepMode::createDeviceTable()
{
    QStandardItemModel *devices = new QStandardItemModel;
    QStandardItem *item;
    //Заголовки столбцов
    QStringList devicehorizontalHeader;
    devicehorizontalHeader.append(" ");

    //Заголовки строк
    QStringList deviceverticalHeader;
    for(int i = 1; i <= numberOfDevices; i++){
        QString devheader = "Device ";
        devheader.append(QString::number(i));
        deviceverticalHeader.append(devheader);
    }


    devices->setHorizontalHeaderLabels(devicehorizontalHeader);
    devices->setVerticalHeaderLabels(deviceverticalHeader);

    for(int i = 0; i < numberOfDevices; i++){
            item = new QStandardItem((steps.getDeviceState()[i]).c_str());
            item->setEditable(false);
            devices->setItem(i, 0, item);
    }


    ui->DeviceTable->setModel(devices);

    ui->DeviceTable->resizeRowsToContents();
    ui->DeviceTable->resizeColumnsToContents();
}

void StepMode::setStep()
{
    ui->StepField->setValidator( new QIntValidator(0, steps.getSize(), this) );
    currentIndex = ui->StepField->text().toInt();
    steps.setIndex(currentIndex);
    //currentIndex = index;
    clearTables();
    phase = 1;
    createGeneratorTable();
}

void StepMode::clearTables(){
    QStandardItemModel *clean = new QStandardItemModel;
    ui->GeneratorTable->setModel(clean);
    ui->DeviceTable->setModel(clean);
    ui->BufferTable->setModel(clean);
    ui->DeniedRequest->clear();
}

void StepMode::on_pushButton_clicked()
{
    if(currentIndex < steps.getSize()){

        if(phase == 0){
            createGeneratorTable();
            phase++;
        }else if(phase == 1){
            createBufferTable();
            ui->DeniedRequest->setText((steps.getDeniedRequest()).c_str());
            phase++;
        }else if(phase == 2){
            createDeviceTable();
            createBufferAfterTable();
            phase = 0;
            steps.increaseIndex();
            currentIndex++;
        }else{
            std::cout << "nah" << std::endl;
        }
        ui->StepField->setText(QString::number(currentIndex));
    }else
        std::cout << "no" << std::endl;
}

void StepMode::on_pushButton_2_clicked()
{
    currentIndex = 0;
    steps.setIndex(0);
    phase = 0;
    clearTables();
}

void StepMode::on_backButton_clicked()
{
    phase = 1;
    if(currentIndex > 1){
        currentIndex-=2;
        steps.setIndex(currentIndex);
        createBufferAfterTable();
        createDeviceTable();
        currentIndex++;
        steps.setIndex(currentIndex);
        createGeneratorTable();
    }else if(currentIndex == 1){
        --currentIndex;
        steps.setIndex(currentIndex);
        clearTables();
        createGeneratorTable();
    }
}

void StepMode::on_SetStepButton_clicked()
{
    setStep();
}
