#include "mainwindow.h"
#include <QApplication>
#include <frmdbtest.h>
#include <QDateTime>
#include <QDebug>
#include <iostream>
#include <myapplication.h>

void msgHandler( QtMsgType type, const char* msg )
{
    const char symbols[] = { 'I', 'E', '!', 'X' };
    QString output = QString("[%1] %2").arg( symbols[type] ).arg( msg );
    std::cerr << output.toStdString() << std::endl;
   // if( type == QtFatalMsg ) abort();
}

int main(int argc, char *argv[])
{
      qInstallMsgHandler( msgHandler );
    int x=10, y=0;
    MyApplication a(argc, argv);
    qDebug() << "Hello world.";
      // qWarning() << "Uh, oh...";
    //   qCritical() << "Oh, noes!";
      // qFatal( "AAAAAAAAAH!" );

//        qDebug() << "INFO: Answer - " << x/y;
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
