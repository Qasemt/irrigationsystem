#ifndef MODELEVENTSLOG_H
#define MODELEVENTSLOG_H

#include <QDateTime>

class ModelEventsLog
{
private:
    int _id;
    int _devicecode    ;
    int  _schedulemode;
    QDateTime _starttime;
    QDateTime _enddate;
    int _durationofsecond;
    int _durationofminute;
    QString  _mobilenumber ;
    int _transferstatus;

public:
    ModelEventsLog();
    int id() const;
    void setId(int id);
    int devicecode() const;
    void setDevicecode(int devicecode);
    int schedulemode() const;
    void setSchedulemode(int schedulemode);
    QDateTime starttime() const;
    void setStarttime(const QDateTime &starttime);
    QDateTime enddate() const;
    void setEnddate(const QDateTime &enddate);
    int durationofsecond() const;
    void setDurationofsecond(int durationofsecond);
    int durationofminute() const;
    void setDurationofminute(int durationofminute);
    QString mobilenumber() const;
    void setMobilenumber(const QString &mobilenumber);
    int transferstatus() const;
    void setTransferstatus(int transferstatus);
};

#endif // MODELEVENTSLOG_H
