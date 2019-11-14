#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool isInfoValid();
    bool isNumeric(const std::string& s);
    ~MainWindow();

private slots:
    void on_beginSimulation_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QTextEdit*> parameters;
};
#endif // MAINWINDOW_H
