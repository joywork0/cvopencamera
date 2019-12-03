#include "mainwindow.h"
#include <QApplication>
#include<QLabel>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   MainWindow w;
    w.show();
//QLabel label("hello world");
//QDebug()<<"ciclk me";
//label.show();
    return a.exec();
}
