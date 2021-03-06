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

QDateTime ModelWeeklyTime::endtime() const
{
    return _endtime;
}

void ModelWeeklyTime::setEndTime(const QDateTime &enddate)
{
    _endtime = enddate;
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


bool ModelWeeklyTime::isTaskActive() const
{
    return _isTaskActive;
}

void ModelWeeklyTime::setIsTaskActive(bool isTaskActive)
{
    _isTaskActive = isTaskActive;
}
ModelWeeklyTime::ModelWeeklyTime()
{

}

