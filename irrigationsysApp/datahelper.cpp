#include "datahelper.h"

DataHelper::DataHelper(QObject *parent) :
    QObject(parent)
{
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
    dbConnect();
    qDebug()<<"intiliz Database "+getdb().databaseName();
    if (!flag)
    {
        dbCreateInstance();
    }
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
    /*
    *Open database, if the database cannot open for
    *any reason print a warning.
    */
    if (!db.open())
    {
        /*
         *Gui message that informs that the database cannot open
         */
       qDebug()<<dbConnectErrorStr + dbCannotOpenStr+ " " +dbFileNameStr;
        /*
         *@return false if database connection failed.
         */
        return false;
    }

    /*
     *@return true if database connection successed
     */
    return db.isOpen();
}

/*
 *disconnects from a database
 */
bool DataHelper::dbDisconnect()
{
    /*
     *close database
     */
    db.close();
    if(!db.isOpen())
    {
        /*
         *@return true if database closed
        */
        return true;
    }
    else
    {
        /*
         *@return false if not closed
         */
        return false;
    }
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
