#include "frmdbtest.h"
#include "ui_frmdbtest.h"
#include <QDebug>
#include <QSqlQuery>
#include <QDesktopWidget>
FrmDBTest::FrmDBTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmDBTest)
{
    ui->setupUi(this);
    ui->setupUi(this);

      //Move the dialog away from the center
      this->setGeometry(0,0,this->width(),this->height());
      //Put the dialog in the screen center
      const QRect screen = QApplication::desktop()->screenGeometry();

      this->move( screen.center() - this->rect().center() );
      //----------------------------

}

FrmDBTest::~FrmDBTest()
{
    delete ui;
}

void FrmDBTest::on_btnGetParams_clicked()
{

    QList<ModelSystemParameter> s =  _bsParams.FillData();

        foreach (ModelSystemParameter vp, s) {
            qDebug()<<vp.getPkeytitle();
        }

}
