#include "mainwindow.h"
#include <QApplication>
#include <frmdbtest.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   MainWindow w;
   // FrmDBTest w;
    w.show();

    return a.exec();
}
