#include "modelweeklytime.h"


int ModelWeeklyTime::id() const
{
    return _id;
}

void ModelWeeklyTime::setId(int id)
{
    _id = id;
}

int ModelWeeklyTime::devicecode() const
{
    return _devicecode;
}

void ModelWeeklyTime::setDevicecode(int devicecode)
{
    _devicecode = devicecode;
}

int ModelWeeklyTime::dayindex() const
{
    return _dayindex;
}

void ModelWeeklyTime::setDayindex(int dayindex)
{
    _dayindex = dayindex;
}

QDateTime ModelWeeklyTime::starttime() const
{
    return _starttime;
}

void ModelWeeklyTime::setStarttime(const QDateTime &starttime)
{
    _starttime = starttime;
}

QDateTime ModelWeeklyTime::enddate() const
{
    return _enddate;
}

void ModelWeeklyTime::setEnddate(const QDateTime &enddate)
{
    _enddate = enddate;
}

int ModelWeeklyTime::durationofsecond() const
{
    return _durationofsecond;
}

void ModelWeeklyTime::setDurationofsecond(int durationofsecond)
{
    _durationofsecond = durationofsecond;
}

int ModelWeeklyTime::durationofminute() const
{
    return _durationofminute;
}

void ModelWeeklyTime::setDurationofminute(int durationofminute)
{
    _durationofminute = durationofminute;
}

bool ModelWeeklyTime::smsalert() const
{
    return _smsalert;
}

void ModelWeeklyTime::setSmsalert(bool smsalert)
{
    _smsalert = smsalert;
}

ModelWeeklyTime::ModelWeeklyTime()
{

}

