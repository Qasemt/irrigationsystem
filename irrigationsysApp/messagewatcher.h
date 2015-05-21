#ifndef MESSAGEWATCHER_H
#define MESSAGEWATCHER_H

#include <QObject>
#include <QObject>
#include <QVariant>
#include <QRegExp>
#include <qdebug.h>

class MessageWatcher: public QObject
{
    Q_OBJECT

private:
    static MessageWatcher *_instance;
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
        if(isCMDDeviceEnable(cmdMessage,cmdnumber,devicenumber,deviceenableStatus))
        {
            emit MessageCMDReceived(QString("cmd number %3 : Device %1  is Enable: %2").arg(QString::number(devicenumber),QString::number(deviceenableStatus),QString::number(cmdnumber)));
        }
        else if(isCMDSetSchedulemode(cmdMessage,cmdnumber,devicenumber,schmode,issmsalert))
        {
            emit MessageCMDReceived(QString("cmd number %1 : Device %2  SCH Mode: %3 is sms alert act %4").arg(QString::number(cmdnumber),QString::number(devicenumber),QString::number(schmode),QString::number(issmsalert)));
        }
        else if(isCMDSetDailytime(cmdMessage,cmdnumber,devicenumber,starttime,durationtime,durationtype,issmsalert))
        {
            emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 duration time %4 dtype : %5 is sms alert %6")
                                    .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,QString::number(durationtime),durationtype,QString::number(issmsalert)));
        }
        else if(isCMDSetweeklytime(cmdMessage,cmdnumber,dayindex,devicenumber,starttime,durationtime,durationtype,issmsalert))
        {
            emit MessageCMDReceived(QString("cmd number %1 : Device %2  start time : %3 duration time %4 dtype : %5 day index %6  is sms alert %7")
                                    .arg(QString::number(cmdnumber),QString::number(devicenumber),starttime,QString::number(durationtime),durationtype,QString::number(dayindex),QString::number(issmsalert)));
        }


    }
private:

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
    bool isCMDSetweeklytime(QString cmdmessage,int &cmdnumber,int &dayindex,int &devicenumber,QString &starttime,int &durationtime,QString &durationtype,bool &issmsalert)
    {
        // $cmd\$(4)@(\d),([1-7]),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\d)@

        QRegExp rx("\\$cmd\\$(4)@(\\d),([1-7]),([0-9]{1,2}\:[0-9]{1,2}),([1-9]{1,5})([m|M|h|H]),(\\d)@");
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

};

#endif // MESSAGEWATCHER_H
