#include "mainwindow.h"
#include <QApplication>
#include <frmdbtest.h>
#include <QDateTime>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // FrmDBTest w;
//    QDateTime sdt=QDateTime::fromString("2015-06-19 03:36:00","yyyy-MM-dd HH:mm:ss");
//    QDateTime nowdt=QDateTime::fromString("2015-06-19 03:37:00","yyyy-MM-dd HH:mm:ss");
//    // if(nowdt>sdt)
//    if(sdt>nowdt)
//    {
//        qDebug()<<"test";
//    }

    w.show();

    return a.exec();
}
