#ifndef MODELDEVICEINFO_H
#define MODELDEVICEINFO_H
#include <aenums.h>
#include <qstring.h>
class ModelDeviceinfo
{
private:
    int _code;
    QString _title;
    bool _powerstatus;
    eSchedulemode _schedulemode;
    bool _deviceenable;
    bool _smsalertenable;

public:
    ModelDeviceinfo();

    int code() const;
    void setCode(int code);
    QString title() const;
    void setTitle(const QString &title);
    bool powerstatus() const;
    void setPowerstatus(bool powerstatus);
    eSchedulemode schedulemode() const;
    void setSchedulemode(int schedulemode);
    bool deviceenable() const;
    void setDeviceenable(bool deviceenable);
    bool smsalertenable() const;
    void setSmsalertenable(bool smsalertenable);
};

#endif // MODELDEVICEINFO_H
