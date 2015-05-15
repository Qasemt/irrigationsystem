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
    MessageWatcher::GetInstance()->FireMessageCMDReceived("fire message :"+ui->txtdeviceinfo->text());
}
