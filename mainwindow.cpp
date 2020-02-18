#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultswindow.h"
#include "stepmode.h"
#include "data.h"
#include "iostream"
#include "smo_manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parameters.push_back(ui->numberOfGenerators);
    parameters.push_back(ui->bufferSize);
    parameters.push_back(ui->numberOfDevices);
    parameters.push_back(ui->numberOfRequests);
    parameters.push_back(ui->alpha);
    parameters.push_back(ui->beta);
    parameters.push_back(ui->lambda);


}

MainWindow::~MainWindow()
{
    delete ui;
}

Data MainWindow::getData(){
    return data;
}

void MainWindow::on_beginSimulation_clicked()
{
    if(isInputValid()){
        getInput();
        ResultsWindow *resultWindow = new ResultsWindow();


        SMOManager *manager = new SMOManager(getData());
        manager->initialize();
        manager->generateRequests();
        manager->start();
        std::cout << "sim ended" << std::endl;
        Step *steps = new Step(manager->returnSteps());
        std::cout << "step created" << std::endl;
        Results res = manager->returnResults();
        std::cout << "res created" << std::endl;
        resultWindow->init(res);
        std::cout << "res init" << std::endl;
        resultWindow->initSteps(*steps);
        std::cout << "res step init" << std::endl;
        resultWindow->move( 600, 250 );
        resultWindow->show();

    }
}

void MainWindow::getInput(){
    Data inputInfo = {};
    toStr(ui->numberOfDevices).empty();
    try {
        inputInfo.numberOfGenerators = ui->numberOfGenerators->toPlainText().toInt();
        inputInfo.bufferSize = ui->bufferSize->toPlainText().toInt();
        inputInfo.numberOfDevices = ui->numberOfDevices->toPlainText().toInt();
        inputInfo.numberOfRequests = ui->numberOfRequests->toPlainText().toInt();
        inputInfo.alpha = ui->alpha->toPlainText().toDouble();//can be zero
        inputInfo.beta = ui->beta->toPlainText().toDouble();
        inputInfo.lambda = ui->lambda->toPlainText().toDouble();

        ui->infoCheck->setText("its ok");
        std::cout << inputInfo.numberOfGenerators << " " <<
                     inputInfo.bufferSize << " " <<
                     inputInfo.numberOfDevices << " " <<
                     inputInfo.numberOfRequests << " " <<
                     inputInfo.alpha << " " <<
                     inputInfo.beta << " " <<
                     inputInfo.lambda << " " << std::endl;
        this->data = inputInfo;
    } catch (const std::exception &e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
        ui->infoCheck->setText(e.what());
    }
}

std::string MainWindow::toStr(QTextEdit *text){
    return text->toPlainText().toStdString();
}

bool MainWindow::isInputValid(){
    //check weird double values
    for(auto parameter : this->parameters){
        if(toStr(parameter).empty()){
            ui->infoCheck->setText("Fill all the fields.");
            return false;
        }
    }
    return true;
}

