#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <imagedelegate.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     // int  r, x=10, y=0;
     // r=x/y;
      //throw "hi...";
    this->setGeometry(0,0,this->width(),this->height());
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();

    this->move( screen.center() - this->rect().center() );
    //this->setWindowFlags(Qt::Window | Qt::Dialog);
    _GsmReader = new GsmReader();

    DataHelper::getInstance();
    _maintimer =new QTimer();
    MessageWatcher::GetInstance();

    connect(_maintimer,SIGNAL(timeout()),this,SLOT(timeoutMaintimer()));
    connect(MessageWatcher::GetInstance(),SIGNAL(MessageCMDReceived(QString)),this,SLOT(onMessageCMDReceived(QString)));
    connect(MessageWatcher::GetInstance(),SIGNAL(DailytimeDataReceived(int,QDateTime,int,int,bool)),this,SLOT(onDailytimeDataReceived(int,QDateTime,int,int,bool)));
    connect(MessageWatcher::GetInstance(),SIGNAL(WeeklytimeDataReceived(int,int,QDateTime,int,int,bool)),this,SLOT(onWeeklytimeDataReceived(int,int,QDateTime,int,int,bool)));
    connect(MessageWatcher::GetInstance(),SIGNAL(SchedulemodeDataReceived(int,int,bool)),this,SLOT(onSchedulemodeDataReceived(int,int,bool)));
    connect(MessageWatcher::GetInstance(),SIGNAL(DeviceEnableDataReceived(int,int)),this,SLOT(onDeviceEnableDataReceived(int,int)));
    connect(MessageWatcher::GetInstance(),SIGNAL(CustomtimeDataReceived(int,QDateTime,int,int,bool)),this,SLOT(onCustomtimeDataReceived(int,QDateTime,int,int,bool)));
    connect(MessageWatcher::GetInstance(),SIGNAL(RefreshData()),this,SLOT(onRefreshData()));
    connect(MessageWatcher::GetInstance(),SIGNAL(DeviceChangeState(int)),this,SLOT(onDeviceChangeState(int)));
    // _maintimer->start(1000);
    _bsCustomTime.ResetTask();
    _BsModelDailyTime.ResetTask();
    _BsWeeklytime.ResetTask();
    _bsCustomTime.ResetTask();
    _bsDeviceinfo.SetPowerOffAllDevice();
    loaddata();
    //---------------
    _deviceProcess1=new DeviceProcess();
    _deviceProcess2=new DeviceProcess();
    _deviceProcess3=new DeviceProcess();
    _deviceProcess4=new DeviceProcess();

    _deviceProcess1->deviceCheck(1);
    _deviceProcess2->deviceCheck(2);
    _deviceProcess3->deviceCheck(3);
    _deviceProcess4->deviceCheck(4);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpen_clicked()
{
    //_GsmReader->Open();

    DataHelper::getInstance()->dbConnect();
}

void MainWindow::on_btnClose_clicked()
{
    DataHelper::getInstance()->dbDisconnect();
}

//---------------------- timer -----------------------
void MainWindow::timeoutMaintimer()
{
    _maintimer->stop();

    _maintimer->start(1000);

}

void MainWindow::loaddata()
{

    _records = new QSqlQueryModel();
    _records->setQuery(_bsDeviceinfo.FillDatasqlmodel());
    //   qDebug()<< q.size();
     _records->insertColumn(6);//icon motor



     _records->setHeaderData(6,Qt::Horizontal,"Image",Qt::DisplayRole);

    /*   _records->setHeaderData(0, Qt::Horizontal, tr("code"));
       model->setHeaderData(1, Qt::Horizontal, tr("title"));
       model->setHeaderData(7, Qt::Horizontal, tr("power status"));
       model->setHeaderData(8, Qt::Horizontal, tr("schedulemode"));
       model->setHeaderData(9, Qt::Horizontal, tr("deviceenable"));
       */

    //-------------------------
    //       code         INT             PRIMARY KEY
    //                                       NOT NULL,
    //          title        VARCHAR( 100 ),
    //          powerstatus  BOOLEAN         DEFAULT ( 0 ),
    //          schedulemode INTEGER         DEFAULT ( 0 ),
    //          deviceenable BOOLEAN         DEFAULT ( 0 )


    // qDebug()<<model->rowCount();
    //-------------------------
    ui->tableView1->setModel(_records);
    QHeaderView *verticalHeader = ui->tableView1->verticalHeader();
    verticalHeader->setResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(68);

   // ui->tableView1->setVerticalHeader(verticalHeader);
    ui->tableView1->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView1->setShowGrid(true);
    ui->tableView1->setItemDelegate(new ImageDelegate(this));

    _Deviceinfo=_bsDeviceinfo.FillData();

}

void MainWindow::on_btnfrmCMDtest_clicked()
{
    _frmCMDTest.show();
}

void MainWindow::onMessageCMDReceived(QString cmdMessage)
{
    qDebug()<<"comming message : "<<cmdMessage << endl;
}

void MainWindow::onDailytimeDataReceived(int devicecode, QDateTime startdatetime, int durationtime, int durationtype, bool issmsalert)
{
    ModelDailyTime model;
    model.setDevicecode(devicecode);
    model.setStarttime(startdatetime);

    int sec=0;
    int min=0;

    if(durationtype==MessageWatcher::TimeDurationType_Minute)//minute
    {
        sec =durationtime*60;
        min=durationtime ;
    }else
    {
        min = durationtime*60;
        sec = min*60;
    }

    model.setEndTime(startdatetime.addSecs(sec));
    model.setDurationofsecond(sec);
    model.setDurationofminute(min);
    model.setSmsalert(issmsalert);
    _BsModelDailyTime.Insert(model);
}

void MainWindow::onWeeklytimeDataReceived(int devicecode, int dayindex, QDateTime startdatetime, int durationtime, int durationtype, bool issmsalert)
{
    ModelWeeklyTime model;
    model.setDevicecode(devicecode);
    model.setStarttime(startdatetime);

    int sec=0;
    int min=0;

    if(durationtype==MessageWatcher::TimeDurationType_Minute)//minute
    {
        sec =durationtime*60;
        min=durationtime ;
    }else
    {
        min = durationtime*60;
        sec = min*60;
    }

    model.setEndTime(startdatetime.addSecs(sec));
    model.setDurationofsecond(sec);
    model.setDurationofminute(min);
    model.setSmsalert(issmsalert);
    model.setDayindex(dayindex);
    _BsWeeklytime.Insert(model);
}

void MainWindow::onCustomtimeDataReceived(int devicecode, QDateTime startdatetime, int durationtime, int durationtype, bool issmsalert)
{
    ModelCustomTime model;
    model.setDevicecode(devicecode);
    model.setStarttime(startdatetime);

    int sec=0;
    int min=0;

    if(durationtype==MessageWatcher::TimeDurationType_Minute)//minute
    {         sec =durationtime*60;
        min=durationtime ;
    }else
    {
        min = durationtime*60;
        sec = min*60;
    }

    model.setEndTime(startdatetime.addSecs(sec));
    model.setDurationofsecond(sec);
    model.setDurationofminute(min);
    model.setSmsalert(issmsalert);
    _bsCustomTime.Insert(model);

}

void MainWindow::onSchedulemodeDataReceived(int devicenumber, int schmode, bool issmsalertActive)
{
    _bsDeviceinfo.UpdateScheduleMode(devicenumber,schmode,issmsalertActive);
}

void MainWindow::onDeviceEnableDataReceived(int devicenumber, int enablestatus)
{
    if(devicenumber<1)
        return;

    _bsDeviceinfo.UpdateDeviceEnableVal(devicenumber,enablestatus);
    switch (devicenumber) {
    case 1:
        if(enablestatus)
            qDebug()<<"Device 1 Active";
        else qDebug()<<"Device 1 DeActive";
        break;
    case 2:
        if(enablestatus)
            qDebug()<<"Device 2 Active";
        else qDebug()<<"Device 2 DeActive";
        break;
    case 3:
        if(enablestatus)
            qDebug()<<"Device 3 Active";
        else qDebug()<<"Device 3 DeActive";
        break;
    case 4:
        if(enablestatus)
            qDebug()<<"Device 4 Active";
        else qDebug()<<"Device 4 DeActive";
        break;
    }
    _Deviceinfo=_bsDeviceinfo.FillData();
}

void MainWindow::onRefreshData()
{
    loaddata();
}

void MainWindow::onDeviceChangeState(int devicenumber)
{
    qDebug()<<QString("Device [%1] Change State").arg(devicenumber);
    loaddata();
}
