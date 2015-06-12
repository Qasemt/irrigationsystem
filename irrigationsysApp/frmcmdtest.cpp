#include "frmcmdtest.h"
#include "ui_frmcmdtest.h"
#include "QDebug"
#include <qdesktopwidget.h>
#include <messagewatcher.h>
FrmCMDTest::FrmCMDTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmCMDTest)
{
    ui->setupUi(this);
    this->setGeometry(0,0,this->width(),this->height());
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();

    this->move( screen.center() - this->rect().center() );
    //----------------------------

}

FrmCMDTest::~FrmCMDTest()
{
    delete ui;
}

void FrmCMDTest::on_btnChangeSchMode_clicked()
{
    int schmodeval=-1;
    if(ui->rdbDialy->isChecked())
        schmodeval=1;
    else if(ui->rdbWeekly->isChecked())
        schmodeval=2;
    if(ui->rdbCustom->isChecked())
        schmodeval=3;

    QString device="1";
  //  QString cmd =QString("$cmd$2@%1,%2,%3@").arg(device,QString::number(schmodeval),QString::number(ui->ckbsmsalret->isChecked()));

        QString	  cmd ="$cmd$2@1,1,0;2,1,0@";

    MessageWatcher::GetInstance()->FireMessageCMDReceived(cmd);
}

void FrmCMDTest::on_btnDeviceEnable_clicked()
{
    if(ui->rdbDeviceenable->isChecked())
    {
        MessageWatcher::GetInstance()->FireMessageCMDReceived(QString("$cmd$1@%1,1@").arg(ui->txtdeviceinfo->text()));
    }else
        if(ui->rdbDevicedisbale->isChecked())
        {
            MessageWatcher::GetInstance()->FireMessageCMDReceived(QString("$cmd$1@%1,0@").arg(ui->txtdeviceinfo->text()));
        }
}

void FrmCMDTest::on_btndialyTime_clicked()
{
     MessageWatcher::GetInstance()->FireMessageCMDReceived(QString("$cmd$3@%1,10:12,33m,1@").arg(ui->txtdeviceinfo->text()));
}

void FrmCMDTest::on_btnweeklytime_clicked()
{
   // MessageWatcher::GetInstance()->FireMessageCMDReceived(QString("$cmd$4@%1,7,10:12,33m,1@").arg(ui->txtdeviceinfo->text()));
     MessageWatcher::GetInstance()->FireMessageCMDReceived(QString("$cmd$4@%1,7,10:12,33m,1@").arg(ui->txtdeviceinfo->text()));
}


void FrmCMDTest::on_btnCMDcustomtime_clicked()
{
    MessageWatcher::GetInstance()->FireMessageCMDReceived(QString("$cmd$5@%1,13930402,10:12,33m,1@").arg(ui->txtdeviceinfo->text()));
}
