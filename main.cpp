#include "mainwindow.h"
#include "form.h"
#include "smo_manager.h"
//#include "data.h"
#include "stepmode.h"
#include <iostream>
//#include <cstdlib>
#include <QApplication>
//#include <QTime>

int main(int argc, char *argv[])
{
//    qsrand(time(0));
    QApplication a(argc, argv);
    MainWindow w;
    w.move( 600, 250 );
    w.show();

    return a.exec();
}
