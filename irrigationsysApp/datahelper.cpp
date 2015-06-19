#include "datahelper.h"

DataHelper::DataHelper(QObject *parent) :
    QObject(parent)
{
    dbConnect();

}



DataHelper * DataHelper::_instance = 0;
QReadWriteLock DataHelper::lock;

DataHelper* DataHelper::getInstance()
{
    if (_instance == 0)
    {
        _instance = new DataHelper;
    }
    return _instance;
}

DataHelper::~DataHelper()
{
    dbDisconnect();
}

int DataHelper::RowCounter(QSqlQuery query)
{
    int cnt=0;

    while (query.next()) {
        cnt++;
    }
    return cnt;
}



/*
 *connect to database
 */
bool DataHelper::dbConnect()
{
    if(isConnected())
    {
        //qDebug()<<"DB Context already Opened";
        return true;
    }

    /*
     *Check the existence of the database driver.
     */
    if (!QSqlDatabase::isDriverAvailable (dbDriverStr))
    {
        /*
        *Gui message that informs that the driver does not exist
        */
        qDebug()<<dbConnectErrorStr + " " + dbDriverNotExistStr ;
        exit(1);
    }

    /*
   *Connect to the database with the following driver.
   */
    db = QSqlDatabase::addDatabase(dbDriverStr);


    bool flag = isDbExist ();
    db.setDatabaseName(dbPathStr +dbFileNameStr);
    qDebug()<<"intiliz Database "+getdb().databaseName();
    if (!db.open())
    {
        qDebug()<<dbConnectErrorStr + dbCannotOpenStr+ " " +dbFileNameStr;
        return false;
    }


    qDebug()<< "Open Database ";
    if (!flag)
    {
        dbCreateInstance();
    }
    return db.isOpen();
}

/*
 *disconnects from a database
 */
bool DataHelper::dbDisconnect()
{
    if(isConnected()==false)
    {
        qDebug()<<"DB Context already Closed";
        return true;
    }

    QString connection;
    connection=db.connectionName();
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
    qDebug()<<"close database";

    if(!db.isOpen())
        return true;
    else
        return false;
}

/*
 *check if database file exist
 */
bool DataHelper::isDbExist()
{
    /*
     *@return true if file exist
     */
    return isFileExist(dbPathStr + dbFileNameStr);
}

/*
 *remove database file
 */
bool DataHelper::dbRemove()
{
    /*
     *@return true if file removed
     */
    return removeFile(dbFileNameStr);
}

/*
 *create a database instance
 */
bool DataHelper::dbCreateInstance()
{
    bool ret = true;

    return ret;
    //   /* create and setup a progress bar. */
    //    int step = 0;
    //    QProgressDialog progress;
    //    progress.setWindowModality(Qt::WindowModal);
    //    progress.setWindowTitle("Creating Database");
    //    progress.setLabelText(dbCreationStr);
    //    progress.setMinimum(step);
    //    progress.setMaximum(PBAR_MAX_STEPS);

    //    /* start progress. */
    //    progress.setValue(++step);

    //    /*
    //     *declare a QSqlQuery object
    //     */
    //    QSqlQuery query;
    //    /*
    //     *check if database is open
    //     */
    //    if(db.isOpen())
    //    {
    //    //progress.setValue(++step);
    //   // ret = query.exec("CREATEe TableName " (Id INTEGER PRIMARY KEY AUTOINCREMENT)");

    //    progress.setValue(++step);

    //    if(!ret)
    //    {
    //        QMessageBox::information(0,dbConnectErrorStr,dbCreationStr);
    //        FileHandler rm;
    //        db.close();
    //        rm.removeFile(dbFileNameStr);
    //    }
    //}
    return ret;
}

QSqlDatabase DataHelper::getdb()
{
    return db;
}

bool DataHelper::isConnected()
{
    return db.isOpen();
}
