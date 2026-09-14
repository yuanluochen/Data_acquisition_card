#include "mainwindow.h"

#include <QApplication>

quint8 test[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

quint8 *ptr = &test[0][1];
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}


