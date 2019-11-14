#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"

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

void MainWindow::on_beginSimulation_clicked()
{
    std::string result = isInfoValid() ? "Valid" : "Not Valid";

    ui->infoCheck->setText(QString::fromStdString(result));
}

bool MainWindow::isInfoValid(){
    bool valid = false;
    for(auto parameter : parameters){
        valid  = isNumeric(parameter->toPlainText().toStdString()) ? true : false;
    }
    return valid;
}

bool MainWindow::isNumeric(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
