#ifndef MESSAGEWATCHER_H
#define MESSAGEWATCHER_H

#include <QObject>

class MessageWatcher: public QObject
{
    Q_OBJECT

private:
    static MessageWatcher *_instance;
public:
    explicit    MessageWatcher(QObject *parent = 0);

    static MessageWatcher* GetInstance()
    {
        int adr = (int)_instance;
        if(adr==0)
        {
            _instance =new MessageWatcher();
        }
        return _instance;
    }

    void FireMessageCMDReceived(QString cmdMessage)
    {
        emit MessageCMDReceived(cmdMessage);
    }


signals:
    void MessageCMDReceived(QString  cmdMessage);

};

#endif // MESSAGEWATCHER_H
