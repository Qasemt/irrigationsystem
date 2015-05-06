#include "gsmreader.h"
#include <QObject>
GsmReader::GsmReader(QObject *parent):serial(0),
    QObject(parent)
{

}

void GsmReader::intilPort()
{

    // serial->setPortName(_portName);
    // QSerialPort::Baud115200

    serial->setBaudRate((BaudRateType)BaudRate);
    serial->setFlowControl(FLOW_OFF);
    serial->setParity(PAR_NONE);
    serial->setDataBits(DATA_8);
    serial->setStopBits(STOP_1);


    connect(serial,SIGNAL(readyRead()),this,SLOT(SerialReceived()));

}
bool GsmReader::Open()
{
    if(serial==0)
        serial = new QextSerialPort();

    if(serial->isOpen()==false)
    {
        serial->setPortName(PortName);
        serial->open(QIODevice::ReadWrite);

        intilPort();

    }
    bool result=serial->isOpen();


    _IsOpenedPort = result;



    if(result)
    {
        serial->reset();
        Log("port "+PortName+" Opened");

    }
    else Log("Can not open port : "+PortName);

    return result;
}

bool GsmReader::Log(QString log)
{
    qDebug()<<log;
}

void GsmReader::SerialReceived()
{

}

