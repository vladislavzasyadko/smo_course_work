#ifndef STEPMODE_H
#define STEPMODE_H

#include "step.h"
#include <boost/algorithm/string.hpp>


#include <QWidget>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class StepMode;
}

class StepMode : public QWidget
{
    Q_OBJECT

public:
    explicit StepMode(QWidget *parent = nullptr);
    void init(int numberOfGenerators, int bufferSize, int numberOfDevices, Step& steps);
    ~StepMode();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_backButton_clicked();

    void on_SetStepButton_clicked();

private:
    int currentIndex;
    Step steps;
    Ui::StepMode *ui;
    int numberOfGenerators;
    int bufferSize;
    int numberOfDevices;
    void createGeneratorTable();
    void createBufferTable();
    void createDeviceTable();
    void setStep();
    int phase;
    void createBufferAfterTable();
    void clearTables();
};

#endif // STEPMODE_H
