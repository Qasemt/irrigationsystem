#ifndef MODELDEVICEINFO_H
#define MODELDEVICEINFO_H

#include <qstring.h>
class ModelDeviceinfo
{
private:
    int _code;
    QString _title;
    bool _powerstatus;
    int _schedulemode;
    bool _deviceenable;

public:
    ModelDeviceinfo();

    int code() const;
    void setCode(int code);
    QString title() const;
    void setTitle(const QString &title);
    bool powerstatus() const;
    void setPowerstatus(bool powerstatus);
    int schedulemode() const;
    void setSchedulemode(int schedulemode);
    bool deviceenable() const;
    void setDeviceenable(bool deviceenable);
};

#endif // MODELDEVICEINFO_H
