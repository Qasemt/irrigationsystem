#include "modeldailytime.h"

ModelDailyTime::ModelDailyTime()
{
}
bool ModelDailyTime::smsalert() const
{
    return _smsalert;
}

void ModelDailyTime::setSmsalert(bool smsalert)
{
    _smsalert = smsalert;
}

int ModelDailyTime::durationofminute() const
{
    return _durationofminute;
}

void ModelDailyTime::setDurationofminute(int durationofminute)
{
    _durationofminute = durationofminute;
}

int ModelDailyTime::durationofsecond() const
{
    return _durationofsecond;
}

void ModelDailyTime::setDurationofsecond(int durationofsecond)
{
    _durationofsecond = durationofsecond;
}

QDateTime ModelDailyTime::enddate() const
{
    return _enddate;
}

void ModelDailyTime::setEnddate(const QDateTime &enddate)
{
    _enddate = enddate;
}

QDateTime ModelDailyTime::starttime() const
{
    return _starttime;
}

void ModelDailyTime::setStarttime(const QDateTime &starttime)
{
    _starttime = starttime;
}

int ModelDailyTime::devicecode() const
{
    return _devicecode;
}

void ModelDailyTime::setDevicecode(int devicecode)
{
    _devicecode = devicecode;
}

int ModelDailyTime::id() const
{
    return _id;
}

void ModelDailyTime::setId(int id)
{
    _id = id;
}

