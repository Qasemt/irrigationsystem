#include "deviceprocess.h"
#include <modelcustomtime.h>
#include <modeldeviceinfo.h>
#include <bsdeviceinfo.h>
#include <aenums.h>
#include <bscustomtime.h>
#include <QDateTime>
#include <QList>
DeviceProcess::DeviceProcess(QObject *parent) :
    QObject(parent)
{

    _maintimer=new QTimer;
    connect(_maintimer,SIGNAL(timeout()),this,SLOT(timeoutMaintimer()));
}
ModelDeviceinfo  _ModelDeviceinfo;
QList<ModelCustomTime> _ModelCustomTimes;
BsDeviceinfo _bsDeviceinfo;
BsCustomTime _BsCustomTime;
int _Devicecode;
void DeviceProcess::deviceCheck(int deviceCode)
{
    _Devicecode=deviceCode;
    LoadData();
    if(_ModelDeviceinfo.code()==-1)
    {
        _ModelDeviceinfo = _bsDeviceinfo.FillbyCode(deviceCode);
    }
    qDebug()<<"Device enable :"+QString::number(_ModelDeviceinfo.code());
    _maintimer->start(1000);
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
    _ModelCustomTimes =_BsCustomTime.FillDatabyCode(_Devicecode);
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


void DeviceProcess::ProcCustomtime()
{
    QDateTime now = QDateTime::currentDateTime();
    foreach (ModelCustomTime model, _ModelCustomTimes) {

        if( _ModelDeviceinfo.powerstatus()==false && now >model.starttime())
        {
            _ModelDeviceinfo.setPowerstatus(true);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process custom time started"<< model.starttime().toString();
        }else
        if(_ModelDeviceinfo.powerstatus()==true && model.enddate()<now  )
        {
            _ModelDeviceinfo.setPowerstatus(false);
            _bsDeviceinfo.Update(_ModelDeviceinfo);
            qDebug()<<now<<"process custom time ended"<< model.enddate().toString();
        }

    }

// qDebug()<<"process custom time started";
}
void DeviceProcess::ProcDilytime()
{
    qDebug()<<"process daily time started";
}
void DeviceProcess::ProcWeeklytime()
{
    qDebug()<<"process weekly time started";
}
