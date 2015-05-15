#ifndef MODELCUSTOMTIME_H
#define MODELCUSTOMTIME_H
#include <QDateTime>

class ModelCustomTime
{
private:
    int _id;
    int _devicecode    ;
    int _dayindex;
    QDateTime _starttime;
    QDateTime _enddate;
    int _durationofsecond;
    int _durationofminute;
    bool _smsalert;

public:
     ModelCustomTime();
    int id() const;
    void setId(int id);
    int devicecode() const;
    void setDevicecode(int devicecode);
    int dayindex() const;
    void setDayindex(int dayindex);
    QDateTime starttime() const;
    void setStarttime(const QDateTime &starttime);
    QDateTime enddate() const;
    void setEnddate(const QDateTime &enddate);
    int durationofsecond() const;
    void setDurationofsecond(int durationofsecond);
    int durationofminute() const;
    void setDurationofminute(int durationofminute);
    bool smsalert() const;
    void setSmsalert(bool smsalert);
};

#endif // MODELCUSTOMTIME_H
