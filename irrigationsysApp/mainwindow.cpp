#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0,0,this->width(),this->height());
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();

    this->move( screen.center() - this->rect().center() );
    _GsmReader = new GsmReader();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpen_clicked()
{
    _GsmReader->Open();
}

void MainWindow::on_btnClose_clicked()
{

}
