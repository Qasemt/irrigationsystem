#ifndef MODELDAILYTIME_H
#define MODELDAILYTIME_H
#include <QDateTime>
class ModelDailyTime
{
public:
    ModelDailyTime();
    int _id;
    int _devicecode    ;
    QDateTime _starttime;
    QDateTime _enddate;
    int _durationofsecond;
    int _durationofminute;
    bool _smsalert;

    int id() const;
    void setId(int id);
    int devicecode() const;
    void setDevicecode(int devicecode);
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

#endif // MODELDAILYTIME_H
