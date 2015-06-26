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
        if(_maintimer->isActive()==false)
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
    for (int i = 0; i < _ModelCustomTimes.length(); ++i) {
        ModelCustomTime model=_ModelCustomTimes[i];


        // qDebug()<<"sss----"<<now<<"---f---"<<model.starttime();
        if( _ModelDeviceinfo.powerstatus()==false && model.isTaskActive()==false && isTimeBetween(now,model.starttime(),model.endtime()))
        {
            _ModelDeviceinfo.setPowerstatus(true);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            _ModelCustomTimes[i].setIsTaskActive(true);
            _BsCustomTime.Update( _ModelCustomTimes[i]);
            qDebug()<<now<<"process custom time started"<< model.starttime().toString();
              MessageWatcher::GetInstance()->FireChangeState(_Devicecode);
        }
        else
            if(_ModelDeviceinfo.powerstatus()==true && model.isTaskActive() &&  isTimeBetween(now,model.starttime(),model.endtime())==false)
            {
                _ModelDeviceinfo.setPowerstatus(false);
                _bsDeviceinfo.Update(_ModelDeviceinfo);

                _ModelCustomTimes[i].setIsTaskActive(false);
                _BsCustomTime.Update( _ModelCustomTimes[i]);
                qDebug()<<now<<"process custom time ended"<< model.endtime().toString();
                   MessageWatcher::GetInstance()->FireChangeState(_Devicecode);
            }

    }

    // qDebug()<<"process custom time started";
}
void DeviceProcess::ProcDilytime()
{
    QDateTime now = QDateTime::currentDateTime();
    for (int i = 0; i < _ModelDailyTimes.length(); ++i) {

        ModelDailyTime model =_ModelDailyTimes[i];
        // qDebug()<<"sss----"<<now<<"---f---"<<model.starttime();
        if( _ModelDeviceinfo.powerstatus()==false && model.isTaskActive()==false && istimebetweenTimeofday(now,model.starttime(),model.endtime()))
        {
            _ModelDeviceinfo.setPowerstatus(true);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            _ModelDailyTimes[i].setIsTaskActive(true);
            _BsModelDailyTime.Update( _ModelDailyTimes[i]);
            qDebug()<<now<<"process dialy time started"<< model.starttime().toString();
              MessageWatcher::GetInstance()->FireChangeState(_Devicecode);
        }
        else
            if(_ModelDeviceinfo.powerstatus()==true && model.isTaskActive() &&  istimebetweenTimeofday(now,model.starttime(),model.endtime())==false)
            {
                _ModelDeviceinfo.setPowerstatus(false);
                _bsDeviceinfo.Update(_ModelDeviceinfo);

                _ModelDailyTimes[i].setIsTaskActive(false);
                _BsModelDailyTime.Update( _ModelDailyTimes[i]);
                qDebug()<<now<<"process dialy time ended"<< model.endtime().toString();
                MessageWatcher::GetInstance()->FireChangeState(_Devicecode);
            }

    }

}
bool DeviceProcess::isTimeBetween(QDateTime time ,QDateTime startTime,QDateTime endTime)
{
    if (endTime < startTime)
    {
        return time <= endTime ||
                time >= startTime;
    }
    else
    {
        return time >= startTime &&
                time <= endTime;
    }
    return false;
}
bool DeviceProcess::istimebetweenTimeofday(QDateTime time ,QDateTime startTime,QDateTime endTime)
{
    if (endTime.time() < startTime.time())
    {
        return time.time() <= endTime.time() ||  time.time() >= startTime.time();
    }
    else
    {
        return time.time() >= startTime.time() &&  time.time() <= endTime.time();
    }
    return false;
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
    //  foreach (ModelWeeklyTime model, _ModelWeeklyTimes) {

    for (int i = 0; i < _ModelWeeklyTimes.length(); ++i) {

        ModelWeeklyTime model =_ModelWeeklyTimes[i];

        // qDebug()<<"sss----"<<now<<"---f---"<<model.starttime();
        if( _ModelDeviceinfo.powerstatus()==false && model.dayindex()== dayofweek && model.isTaskActive()==false && istimebetweenTimeofday(now,model.starttime(),model.endtime()))
        {
            _ModelDeviceinfo.setPowerstatus(true);
            _bsDeviceinfo.Update(_ModelDeviceinfo);

            _ModelWeeklyTimes[i].setIsTaskActive(true);
            _BsWeeklytime.Update( _ModelWeeklyTimes[i]);
            qDebug()<<now<<"process custom time started"<< model.starttime().toString();
             MessageWatcher::GetInstance()->FireChangeState(_Devicecode);
        }
        else
            if(_ModelDeviceinfo.powerstatus()==true && model.isTaskActive() &&  istimebetweenTimeofday(now,model.starttime(),model.endtime())==false)
            {
                _ModelDeviceinfo.setPowerstatus(false);
                _bsDeviceinfo.Update(_ModelDeviceinfo);

                _ModelWeeklyTimes[i].setIsTaskActive(false);
                _BsWeeklytime.Update( _ModelWeeklyTimes[i]);

                qDebug()<<now<<"process custom time ended"<< model.endtime().toString();
                  MessageWatcher::GetInstance()->FireChangeState(_Devicecode);
            }

    }

}
