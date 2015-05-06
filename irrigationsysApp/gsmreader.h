#ifndef GSMREADER_H
#define GSMREADER_H
#include <QtExtSerialPort/qextserialport.h>
#include <QDebug>
class GsmReader : public QObject
{
     Q_OBJECT
public:
    GsmReader(QObject *parent = 0);

    bool _IsOpenedPort;
    bool Open();
    QString PortName;
     int BaudRate;
    void intilPort();
private :
    QextSerialPort  *serial;

    bool Log(QString log);
private slots:
    void SerialReceived();
};

#endif // GSMREADER_H
