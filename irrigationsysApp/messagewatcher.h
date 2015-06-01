#ifndef MESSAGEWATCHER_H
#define MESSAGEWATCHER_H

#include <QObject>
#include <QObject>
#include <QVariant>
#include <QRegExp>
#include <qdebug.h>
#include <qdateconvertor.h>

#include <bsdeviceinfo.h>
#include <bscustomtime.h>
#include <bsweeklytime.h>
#include <bsmodeldailytime.h>

class MessageWatcher: public QObject
{
    Q_OBJECT

private:
    static MessageWatcher *_instance;
    QDateConvertor _qdateconvertor;
    QString toMiladi(int year,int month,int day,int hour,int minute,int second)
    {

        QDateConvertor mdate;
        QStringList miladi=  mdate.ToMiladi(QString::number(year),QString::number(month),QString::number(day));
        year =miladi.at(0).toInt();
        month =miladi.at(1).toInt();
        day =miladi.at(2).toInt();

        QString    miladiFullDateTime = miladi.at(0)+"/"+miladi.at(1)+"/"+miladi.at(2) + " "+mdate.ZeroPadding(hour,2)+ ":"+mdate.ZeroPadding(minute,2)+":"+mdate.ZeroPadding(second,2);

        return miladiFullDateTime;
    }
    QDateTime ToDatetime(int year,int month,int day,int hour,int minute,int second)
    {
        QDateTime result;
        if(year>2000)
            result = QDateTime(QDate(year,month,day),QTime(hour,minute,second));
        else{

            QString miladiFullDateTime= toMiladi(year,month,day,hour,minute,second);
            result= QDateTime::fromString(miladiFullDateTime,"yyyy/MM/dd HH:mm:ss");
        }
        return result;
    }

public:
    explicit    MessageWatcher(QObject *parent = 0);

    static MessageWatcher* GetInstance()
    {
        int adr = (int)_instance;
        if(adr==0)
        {
            _instance =new MessageWatcher();
        }
        return _instance;
    }
    enum TimeDurationType
    {
        TimeDurationType_Minute=1,
        TimeDurationType_Hour=2
    };
    void FireMessageCMDReceived(QString cmdMessage)
    {
        devicenumber =0;
        deviceenableStatus=false;
        cmdnumber=0;
        int schmode=0;
        bool issmsalert=0;
        QString starttime="";
        int durationtime=0;
        QString durationtype="";
        int dayindex=0;
        QString  strDate="";
        int year=0;
        int month=0;
        int day=0;
        int hour=0;
        int minute=0;


        if(isCMDDeviceEnable(cmdMessage,cmdnumber,devicenumber,deviceenableStatus))
        {

            emit DeviceEnableDataReceived(devicenumber,deviceenableStatus);
            emit MessageCMDReceived(QString("cmd number %3 : Device %1  is Enable: %2").arg(QString::number(devicenumber),QString::number(deviceenableStatus),QString::number(cmdnumber)));
        }
        else if(isCMDSetSchedulemode(cmdMessage,cmdnumber,devicenumber,schmode,issmsalert))
        {

            emit SchedulemodeDataReceived(devicenumber,schmode,issmsalert);
            emit MessageCMDReceived(QString("cmd number %1 : Device %2  SCH Mode: %3 is sms alert act %4").arg(QString::number(cmdnumber),QString::number(devicenumber),QString::number(schmode),QString::number(issmsalert)));
        }
        else if(isCMDSetDailytime(cmdMessage,cmdnumber,devicenumber,starttime,durationtime,durationtype,issmsalert))
        {

            QDateTime startdate ;
            QDateTime currentdt=QDateTime::currentDateTime();
            year=currentdt.date().year();
            month=currentdt.date().month();
            day=currentdt.date().day();



            if(starttime.length()==5)
            {
                hour=  starttime.mid(0,2).toInt();
                minute= starttime.mid(3,2).toInt();
            }

            startdate =ToDatetime(year,month,day,hour,minute,0);
            TimeDurationType tdt;
            if(durationtype=="m" || durationtype=="M")
                tdt=TimeDurationType_Minute;
            else tdt=TimeDurationType_Hour;

               _BsModelDailyTime.RemoveAll();
            emit DailytimeDataReceived(devicenumber,startdate,durationtime,tdt,issmsalert);

            emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 duration time %4 dtype : %5 is sms alert %6")
                                    .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,QString::number(durationtime),durationtype,QString::number(issmsalert)));
        }
        else if(isCMDSetweeklytime(cmdMessage,cmdnumber,dayindex,devicenumber,starttime,durationtime,durationtype,issmsalert))
        {


            QDateTime startdate ;
             QDateTime currentdt=QDateTime::currentDateTime();
            year=currentdt.date().year();
            month=currentdt.date().month();
            day=currentdt.date().day();

            if(starttime.length()==5)
            {
                hour=  starttime.mid(0,2).toInt();
                minute= starttime.mid(3,2).toInt();
            }

            startdate =ToDatetime(year,month,day,hour,minute,0);

            TimeDurationType tdt;
            if(durationtype=="m" || durationtype=="M")
                tdt=TimeDurationType_Minute;
            else tdt=TimeDurationType_Hour;

             _BsWeeklytime.RemoveAll();
            emit WeeklytimeDataReceived(devicenumber,dayindex,startdate,durationtime,tdt,issmsalert);


            emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 duration time %4 dtype : %5 day index %6  is sms alert %7")
                                    .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,QString::number(durationtime),durationtype,QString::number(dayindex),QString::number(issmsalert)));
        }
        else if(isCMDSetCustomtime(cmdMessage,cmdnumber,devicenumber,starttime,strDate,durationtime,durationtype,issmsalert))
        {

            QDateTime startdate ;
            if(strDate.length()==8)
            {
                year=strDate.mid(0,4).toInt();
                month=strDate.mid(4,2).toInt();
                day=strDate.mid(6,2).toInt();


            }
            if(starttime.length()==5)
            {
                hour=  starttime.mid(0,2).toInt();
                minute= starttime.mid(3,2).toInt();
            }


            startdate =ToDatetime(year,month,day,hour,minute,0);

            TimeDurationType tdt;
            if(durationtype=="m" || durationtype=="M")
                tdt=TimeDurationType_Minute;
            else tdt=TimeDurationType_Hour;

              _bsCustomTime.RemoveAll();

            emit CustomtimeDataReceived(devicenumber,startdate,durationtime,tdt,issmsalert);


            emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 start date %4 duration time %5 dtype : %6 is sms alert %7")
                                    .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,strDate,QString::number(durationtime),durationtype,QString::number(issmsalert)));
        }


    }
private:
    BsDeviceinfo _bsDeviceinfo;
    BsCustomTime _bsCustomTime;
    BsWeeklytime _BsWeeklytime;
    BsModelDailyTime _BsModelDailyTime;

    int devicenumber;
    bool deviceenableStatus;
    int cmdnumber;
    //---------------- CMD validation -----------------------

    bool isCMDDeviceEnable(QString cmdmessage,int &cmdnumber,int &devicenumber,bool &status)
    {
        // QRegExp rx("\\$cmd\\$(\\d*)@(\\d),(\\d)@");
        QRegExp rx("\\$cmd\\$(1)@(\\d),(\\d)@");
        //$cmd$1@1,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            cmdnumber = rx.cap(1).toInt();//cmd number
            devicenumber = rx.cap(2).toInt();// device number
            status = rx.cap(3).toInt();// enable/disable
            result=true;
            // qDebug()<<cap1<<QString::number(devicenumber);
        }
        return result;
    }


    bool isCMDSetSchedulemode(QString cmdmessage,int &cmdnumber,int &devicenumber,int &schmode,bool &issmsalert)
    {

        QRegExp rx("\\$cmd\\$(2)@(\\d),(\\d),(\\d)@");
        //$cmd$1@1,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            cmdnumber = rx.cap(1).toInt();//cmd number
            devicenumber = rx.cap(2).toInt();// device number
            schmode = rx.cap(3).toInt();//sch mode
            issmsalert = rx.cap(4).toInt();// sms alert
            result=true;
        }
        return result;
    }

    bool isCMDSetDailytime(QString cmdmessage,int &cmdnumber,int &devicenumber,QString &starttime,int &durationtime,QString &durationtype,bool &issmsalert)
    {
        // \$cmd\$(3)@(\d),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\d)@

        QRegExp rx("\\$cmd\\$(3)@(\\d),([0-9]{1,2}\\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\\d)@");
        //$cmd$3@1,10:12,33m,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            cmdnumber = rx.cap(1).toInt();//cmd number
            devicenumber = rx.cap(2).toInt();// device number
            starttime = rx.cap(3);
            durationtime = rx.cap(4).toInt();
            durationtype =rx.cap(5);
            issmsalert = rx.cap(6).toInt();// sms alert
            result=true;
        }
        return result;
    }

    bool isCMDSetCustomtime(QString cmdmessage,int &cmdnumber,int &devicenumber,QString &strTime,QString &strDate,int &durationtime,QString &durationtype,bool &issmsalert)
    {
        // \$cmd\$(5)@(\d),(\d{8}),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\d)@

        QRegExp rx("\\$cmd\\$(5)@(\\d),(\\d{8}),([0-9]{1,2}\\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\\d)@");
        //$cmd$4@1,930402,10:12,33m,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {
            cmdnumber = rx.cap(1).toInt();//cmd number
            devicenumber = rx.cap(2).toInt();// device number
            strDate  = rx.cap(3); //time
            strTime  =rx.cap(4);  // date
            durationtime = rx.cap(5).toInt(); // m/h
            durationtype =rx.cap(6);
            issmsalert = rx.cap(7).toInt();// sms alert
            result=true;
        }
        return result;
    }

    bool isCMDSetweeklytime(QString cmdmessage,int &cmdnumber,int &dayindex,int &devicenumber,QString &starttime,int &durationtime,QString &durationtype,bool &issmsalert)
    {
        // $cmd\$(4)@(\d),([1-7]),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\d)@

        QRegExp rx("\\$cmd\\$(4)@(\\d),([1-7]),([0-9]{1,2}\\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\\d)@");
        //$cmd$4@1,7,00:12,33m,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            cmdnumber = rx.cap(1).toInt();//cmd number
            devicenumber = rx.cap(2).toInt();// device number
            dayindex=rx.cap(3).toInt(); //day index
            starttime = rx.cap(4);
            durationtime = rx.cap(5).toInt();
            durationtype =rx.cap(6);
            issmsalert = rx.cap(7).toInt();// sms alert
            result=true;

        }
        return result;
    }






signals:
    void MessageCMDReceived(QString  cmdMessage);
    void DailytimeDataReceived(int devicenumber,QDateTime startdatetime,int durationtime,int durationtype,bool issmsalert);
    void WeeklytimeDataReceived(int devicenumber,int dayindex,QDateTime startdatetime,int durationtime,int durationtype,bool issmsalert);
    void CustomtimeDataReceived(int devicenumber,QDateTime startdatetime,int durationtime,int durationtype,bool issmsalert);
    void SchedulemodeDataReceived(int devicenumber,int schmode,bool issmsalertActive);
    void DeviceEnableDataReceived(int devicenumber,int enablestatus);

};

#endif // MESSAGEWATCHER_H
