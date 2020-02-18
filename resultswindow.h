#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QMainWindow>
#include "results.h"
#include "step.h"
#include "stepmode.h"

namespace Ui {
class ResultsWindow;
}

class ResultsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultsWindow(QWidget *parent = nullptr);
    void init(Results data);
    void initSteps(Step steps);
    void createMainTable();
    void createDeviceTable();
    ~ResultsWindow();

private slots:
    void on_StepMode_clicked();

private:
    Ui::ResultsWindow *ui;
    Results data;
    Step steps;
};

#endif // RESULTSWINDOW_H
