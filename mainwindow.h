#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include "data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void getInput();
    Data getData();
    std::string toStr(QTextEdit *text);
    bool isInputValid();
    ~MainWindow();

private slots:
    void on_beginSimulation_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QTextEdit*> parameters;
    Data data;
};
#endif // MAINWINDOW_H
