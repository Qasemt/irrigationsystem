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
    void FireChangeState(int devicenumber)
    {
        emit DeviceChangeState(devicenumber);
    }
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


        if(getCMDNumber(cmdMessage,cmdnumber)==false)
            return ;

        if(cmdnumber==1)//enable/disable device
        {

            QStringList recs=   getCMDData(cmdMessage);
            foreach (QString rec, recs) {

                if(isCMDDeviceEnable(rec,devicenumber,deviceenableStatus))
                {

                    emit DeviceEnableDataReceived(devicenumber,deviceenableStatus);
                    emit MessageCMDReceived(QString("cmd number %3 : Device %1  is Enable: %2").arg(QString::number(devicenumber),QString::number(deviceenableStatus),QString::number(cmdnumber)));
                }

            }
            emit RefreshData();
        }


        else


            if(cmdnumber==2) //schedule mode
            {
                QStringList recs=   getCMDData(cmdMessage);
                foreach (QString rec, recs) {
                    if(isCMDSetSchedulemode(rec,devicenumber,schmode,issmsalert))
                    {

                        emit SchedulemodeDataReceived(devicenumber,schmode,issmsalert);
                        emit MessageCMDReceived(QString("cmd number %1 : Device %2  SCH Mode: %3 is sms alert act %4").arg(QString::number(cmdnumber),QString::number(devicenumber),QString::number(schmode),QString::number(issmsalert)));
                    }
                }

                emit RefreshData();
            }
            else     if(cmdnumber==3)
            {
                QStringList recs=   getCMDData(cmdMessage);
                _BsModelDailyTime.RemoveAll();
                foreach (QString rec, recs) {

                    if(isCMDSetDailytime(rec,devicenumber,starttime,durationtime,durationtype,issmsalert))
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


                        emit DailytimeDataReceived(devicenumber,startdate,durationtime,tdt,issmsalert);

                        emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 duration time %4 dtype : %5 is sms alert %6")
                                                .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,QString::number(durationtime),durationtype,QString::number(issmsalert)));
                    }
                }
                emit RefreshData();
            }
            else    if(cmdnumber==4)
            {
                _BsWeeklytime.RemoveAll();
                QStringList recs=   getCMDData(cmdMessage);
                foreach (QString rec, recs) {


                    if(isCMDSetweeklytime(rec,dayindex,devicenumber,starttime,durationtime,durationtype,issmsalert))
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


                        emit WeeklytimeDataReceived(devicenumber,dayindex,startdate,durationtime,tdt,issmsalert);


                        emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 duration time %4 dtype : %5 day index %6  is sms alert %7")
                                                .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,QString::number(durationtime),durationtype,QString::number(dayindex),QString::number(issmsalert)));
                    }
                }
                emit RefreshData();
            }

            else     if(cmdnumber==5)
            {
                _bsCustomTime.RemoveAll();
                QStringList recs=   getCMDData(cmdMessage);

                foreach (QString rec, recs) {

                    if(isCMDSetCustomtime(rec,devicenumber,starttime,strDate,durationtime,durationtype,issmsalert))
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



                        emit CustomtimeDataReceived(devicenumber,startdate,durationtime,tdt,issmsalert);


                        emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 start date %4 duration time %5 dtype : %6 is sms alert %7")
                                                .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,strDate,QString::number(durationtime),durationtype,QString::number(issmsalert)));
                    }
                }
                emit RefreshData();
            }


            else    if(cmdnumber==6)//sms enable/ sms disable device
            {

                QStringList recs=   getCMDData(cmdMessage);
                foreach (QString rec, recs) {
                    bool smsAccessStatus=0;
                    if(isCMDDeviceSMSEnable(rec,devicenumber,smsAccessStatus))
                    {

                        emit DeviceSMSStatusDataReceived(devicenumber,smsAccessStatus);
                        emit MessageCMDReceived(QString("cmd number %3 : Device %1  is [sms] Enable: %2").arg(QString::number(devicenumber),QString::number(smsAccessStatus),QString::number(cmdnumber)));
                    }

                }
                emit RefreshData();
            }

            else    if(cmdnumber==7) //Query device Status
            {
                // QStringList recs=   getCMDData(cmdMessage);
                emit QueryDeviceStatusDataReceived();
                emit MessageCMDReceived(QString("Query cmd number %1 ").arg(QString::number(cmdnumber)));
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

    bool isCMDDeviceEnable(QString cmdmessage,int &devicenumber,bool &status)
    {

        QRegExp rx("(\\d),(\\d)");
        //@1,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            devicenumber = rx.cap(1).toInt();// device number
            status = rx.cap(2).toInt();// enable/disable
            result=true;
            // qDebug()<<cap1<<QString::number(devicenumber);
        }
        return result;
    }

    bool isCMDDeviceSMSEnable(QString cmdmessage,int &devicenumber,bool &status)
    {

        QRegExp rx("(\\d),(\\d)");
        //@1,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            devicenumber = rx.cap(1).toInt();// device number
            status = rx.cap(2).toInt();// enable/disable
            result=true;
            // qDebug()<<cap1<<QString::number(devicenumber);
        }
        return result;
    }

    bool isCMDSetSchedulemode(QString cmdmessage,int &devicenumber,int &schmode,bool &issmsalert)
    {

        QRegExp rx("(\\d),(\\d),(\\d)");

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {


            devicenumber = rx.cap(1).toInt();// device number
            schmode = rx.cap(2).toInt();//sch mode
            issmsalert = rx.cap(3).toInt();// sms alert
            result=true;
        }
        return result;
    }

    bool isCMDSetDailytime(QString cmdmessage,int &devicenumber,QString &starttime,int &durationtime,QString &durationtype,bool &issmsalert)
    {
        //@(\d),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\d)@

        QRegExp rx("(\\d),([0-9]{1,2}\\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\\d)");
        //@1,10:12,33m,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {


            devicenumber = rx.cap(1).toInt();// device number
            starttime = rx.cap(2);
            durationtime = rx.cap(3).toInt();
            durationtype =rx.cap(4);
            issmsalert = rx.cap(5).toInt();// sms alert
            result=true;
        }
        return result;
    }

    bool isCMDSetCustomtime(QString cmdmessage,int &devicenumber,QString &strTime,QString &strDate,int &durationtime,QString &durationtype,bool &issmsalert)
    {
        //@(\d),(\d{8}),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\d)@

        QRegExp rx("(\\d),(\\d{8}),([0-9]{1,2}\\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\\d)");
        //@1,930402,10:12,33m,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            devicenumber = rx.cap(1).toInt();// device number
            strDate  = rx.cap(2); //time
            strTime  =rx.cap(3);  // date
            durationtime = rx.cap(4).toInt(); // m/h
            durationtype =rx.cap(5);
            issmsalert = rx.cap(6).toInt();// sms alert
            result=true;
        }
        return result;
    }

    bool isCMDSetweeklytime(QString cmdmessage,int &dayindex,int &devicenumber,QString &starttime,int &durationtime,QString &durationtype,bool &issmsalert)
    {
        //@(\d),([1-7]),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\d)@

        QRegExp rx("(\\d),([1-7]),([0-9]{1,2}\\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\\d)");
        //@1,7,00:12,33m,1@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {


            devicenumber = rx.cap(1).toInt();// device number
            dayindex=rx.cap(2).toInt(); //day index
            starttime = rx.cap(3);
            durationtime = rx.cap(4).toInt();
            durationtype =rx.cap(5);
            issmsalert = rx.cap(6).toInt();// sms alert
            result=true;

        }
        return result;
    }


    bool getCMDNumber(QString cmdmessage, int &cmdnumber )
    {
        QRegExp rx("\\$cmd\\$(\\d)@");
        //$cmd$4@

        bool result=false;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            cmdnumber = rx.cap(1).toInt();//cmd number
            result=true;

        }
        return result;
    }

    QStringList getCMDData(QString cmdmessage )
    {
        QRegExp rx("\\@(.*)\\@");


        QStringList result;
        int pos =rx.indexIn(cmdmessage);
        if (pos > -1) {

            QString body= rx.cap(1);
            result=  body.split(";");


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
    void DeviceSMSStatusDataReceived(int devicenumber,int status);
    void QueryDeviceStatusDataReceived();

    void RefreshData();
    void DeviceChangeState(int devicenumber);
};

#endif // MESSAGEWATCHER_H
