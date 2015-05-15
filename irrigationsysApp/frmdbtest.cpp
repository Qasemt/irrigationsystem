#include "frmdbtest.h"
#include "ui_frmdbtest.h"
#include <QDebug>
#include <QSqlQuery>
#include <QDesktopWidget>
#include <bsmodeldailytime.h>

FrmDBTest::FrmDBTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmDBTest)
{
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


void FrmDBTest::on_btnDailyTime1_clicked()
{
    BsModelDailyTime bs;
    ModelDailyTime mdl;
    mdl.setDevicecode(1);
    QDate dt(2015,1,1);
    QTime stime(10,22,0);
    QTime etime(11,1,1);
    mdl.setStarttime(QDateTime(dt,stime));
    mdl.setEnddate(QDateTime(dt,etime));
    mdl.setDurationofsecond(mdl.starttime().secsTo(mdl.enddate()));
    mdl.setDurationofminute(mdl.durationofsecond()/60);

    bool res=  bs.Insert(mdl);
    qDebug()<<QString::number(res);
}

void FrmDBTest::on_btnDailyTimeupdate_clicked()
{
    BsModelDailyTime bs;
    ModelDailyTime mdl;
  //  mdl.setId(26);
    mdl.setDevicecode(1);
    QDate dt(2015,1,1);
    QTime stime(10,23,0);
    QTime etime(11,1,2);
    mdl.setStarttime(QDateTime(dt,stime));
    mdl.setEnddate(QDateTime(dt,etime));
    int r =mdl.starttime().secsTo(mdl.enddate());
    mdl.setDurationofsecond(r);
    mdl.setDurationofminute(r/60);

    bool res=  bs.Update(mdl);
    qDebug()<<QString::number(res);
}
