#ifndef DATAHELPER_H
#define DATAHELPER_H
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QReadWriteLock>
#include<qsqlerror.h>
#include <QReadWriteLock>
#include <QObject>
#include <qfile.h>
#include <QDebug>

/*
 * declare DB driver and filename.
 */
static const QString dbDriverStr = "QSQLITE";
static const QString dbFileNameStr = "data.db3";
//static const QString dbPathStr = "/home/qasem/devtools/irrigationsystem/irrigationsysApp/";
static const QString dbPathStr = "/home/qasem/gitsrc/irrigationsystem/irrigationsysApp/";
static const int PBAR_MAX_STEPS =7;

/*
 * GUI string messages.
 */
static QString dbConnectErrorStr = "Database Connection Error";
static QString dbDriverNotExistStr = "Database driver is not available.";
static QString dbCannotOpenStr ="The database cannot open.";
static const QString dbCreationStr ="Creating a database instance failed";

class DataHelper : public QObject
{
    Q_OBJECT
public:
    explicit DataHelper(QObject *parent = 0);

private:
    static DataHelper * _instance;

protected:
   // DataHelper();

    QSqlDatabase db;

public: static DataHelper * getInstance();
    bool dbConnect();
    bool isConnected();
    bool dbDisconnect();
    bool isDbExist();
    bool dbRemove();
    bool dbCreateInstance();
    QSqlDatabase getdb();
    ~DataHelper();
      static int RowCounter(QSqlQuery query);
     static QReadWriteLock lock;


private :
     bool isFileExist(QString fileName)
     {
         bool ret= false;
         ret = QFile::exists(fileName);
         if(ret == false)
         {
             return ret;
         }
         return ret;
     }



     bool removeFile(QString fileName)
     {
         bool ret = false;
         ret = QFile::remove(fileName);
         if(ret == false)
         {
             return ret;
         }
         return ret;
     }

};

#endif // DATAHELPER_H
