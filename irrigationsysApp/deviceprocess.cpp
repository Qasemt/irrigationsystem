#include "deviceprocess.h"


DeviceProcess::DeviceProcess(QObject *parent) :
    QObject(parent)
{

    _maintimer=new QTimer;
    connect(_maintimer,SIGNAL(timeout()),this,SLOT(timeoutMaintimer()));
    connect(MessageWatcher::GetInstance(),SIGNAL(RefreshData()),this,SLOT(onRefreshData()));
}

void DeviceProcess::deviceCheck(int deviceCode)
{
    _Devicecode=deviceCode;
    LoadData();
    if(_ModelDeviceinfo.code()==-1)
    {
        _ModelDeviceinfo = _bsDeviceinfo.FillbyCode(deviceCode);
    }

    //    if(_ModelDeviceinfo.powerstatus())
    //    {
    //       _ModelDeviceinfo.setPowerstatus(false);
    //        _bsDeviceinfo.Update(_ModelDeviceinfo);
    //          _maintimer =new QTimer();
    //            _maintimer->start(1000);
    //    }else
    //    {
    //        _ModelDeviceinfo.setPowerstatus(true);
    //        _bsDeviceinfo.Update(_ModelDeviceinfo);
    //    }
}

void DeviceProcess::LoadData()
{
    qDebug()<<"Device Process -> Method Loaddata() "<<"---------- Device "<<_Devicecode;
    _ModelDeviceinfo = _bsDeviceinfo.FillbyCode(_Devicecode);
    _ModelCustomTimes =_BsCustomTime.FillDatabyCode(_Devicecode);
    _ModelDailyTimes =_BsModelDailyTime.FillDatabyCode(_Devicecode);
    _ModelWeeklyTimes=_BsWeeklytime.FillDatabyCode(_Devicecode);
    if( _ModelDeviceinfo.deviceenable())
    {
        qDebug()<<QString("Device [%1] enable  ").arg(QString::number(_ModelDeviceinfo.code()));
        if(_maintimer->isActive())
            _maintimer->start(1000);
    }else{
        qDebug()<<QString("Device [%1] disable  ").arg(QString::number(_ModelDeviceinfo.code()));
        _maintimer->stop();
    }

}

void DeviceProcess::timeoutMaintimer()
{
    _maintimer->stop();
    switch (_ModelDeviceinfo.schedulemode()) {
    case schedulemode_custom:
        ProcCustomtime();
        break;
    case schedulemode_daily:
        ProcDilytime();
        break;
    case schedulemode_weekly:
        ProcWeeklytime();
        break;

    }
    _maintimer->start(1000);
}

void DeviceProcess::onRefreshData()
{
    LoadData();
}


void DeviceProcess::ProcCustomtime()
{
    QDateTime now = QDateTime::currentDateTime();
    foreach (ModelCustomTime model, _ModelCustomTimes) {

        // qDebug()<<"sss----"<<now<<"---f---"<<model.starttime();
        if( _ModelDeviceinfo.powerstatus()==false && now>model.starttime() && now<model.endtime())
        {
            _ModelDeviceinfo.setPowerstatus(true);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process custom time started"<< model.starttime().toString();
        }

        if(_ModelDeviceinfo.powerstatus()==true && now >model.endtime()  )
        {
            _ModelDeviceinfo.setPowerstatus(false);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process custom time ended"<< model.endtime().toString();
        }

    }

    // qDebug()<<"process custom time started";
}
void DeviceProcess::ProcDilytime()
{
    QDateTime now = QDateTime::currentDateTime();
    foreach (ModelDailyTime model, _ModelDailyTimes) {

        // qDebug()<<"sss----"<<now<<"---f---"<<model.starttime();
        if( _ModelDeviceinfo.powerstatus()==false && now>model.starttime() && now<model.endtime())
        {
            _ModelDeviceinfo.setPowerstatus(true);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process dialy time started"<< model.starttime().toString();
        }

        if(_ModelDeviceinfo.powerstatus()==true && now >model.endtime()  )
        {
            _ModelDeviceinfo.setPowerstatus(false);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process dialy time ended"<< model.endtime().toString();
        }

    }

}
void DeviceProcess::ProcWeeklytime()
{
    QDateTime now = QDateTime::currentDateTime();
    int dayofweek =now.date().dayOfWeek();
    //    1 = "Monday"
    //    2 = "Tuesday"
    //    3 = "Wednesday"
    //    4 = "Thursday"
    //    5 = "Friday"
    //    6 = "Saturday"
    //    7 = "Sunday"
    foreach (ModelWeeklyTime model, _ModelWeeklyTimes) {

        // qDebug()<<"sss----"<<now<<"---f---"<<model.starttime();
        if( _ModelDeviceinfo.powerstatus()==false && model.dayindex()== dayofweek && now>model.starttime() && now<model.endtime())
        {
            _ModelDeviceinfo.setPowerstatus(true);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process custom time started"<< model.starttime().toString();
        }

        if(_ModelDeviceinfo.powerstatus()==true && model.dayindex()== dayofweek &&  now >model.endtime()  )
        {
            _ModelDeviceinfo.setPowerstatus(false);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process custom time ended"<< model.endtime().toString();
        }

    }

}
