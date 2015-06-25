#ifndef MODELWEEKLYTIME_H
#define MODELWEEKLYTIME_H

#include <QDateTime>

class ModelWeeklyTime
{
private:
    int _id;
    int _devicecode    ;
    int _dayindex;
    QDateTime _starttime;
    QDateTime _endtime;
    int _durationofsecond;
    int _durationofminute;
    bool _smsalert;
    bool _isTaskActive;
public:
    ModelWeeklyTime();
    int id() const;
    void setId(int id);

    int devicecode() const;
    void setDevicecode(int devicecode);

    int dayindex() const;
    void setDayindex(int dayindex);

    QDateTime starttime() const;
    void setStarttime(const QDateTime &starttime);

    QDateTime endtime() const;
    void setEndTime(const QDateTime &endtime);

    int durationofsecond() const;
    void setDurationofsecond(int durationofsecond);

    int durationofminute() const;
    void setDurationofminute(int durationofminute);

    bool smsalert() const;
    void setSmsalert(bool smsalert);

    bool isTaskActive() const;
    void setIsTaskActive(bool isTaskActive);

private:
};

#endif // MODELWEEKLYTIME_H
