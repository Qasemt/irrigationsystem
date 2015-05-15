#include "basebusiness.h"

baseBusiness::baseBusiness()
{

}

QSqlQuery baseBusiness::FillData()
{
    QSqlQuery   query;
    DataHelper::lock.lockForRead();

    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            query = QSqlQuery(DataHelper::getInstance()->getdb());
            QString str= "select * from "+_TableName;

            query.exec(str);
        }
    }
    catch(...)
    {
        qDebug()<<"ERROR";
    }
    DataHelper::lock.unlock();

    return query;
}

bool baseBusiness::Update( QMap<QString, QVariant> params, QString whereparams)
{
    DataHelper::lock.lockForWrite();

    bool result=false;
    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            QMapIterator<QString, QVariant> i(params);
            QString fields;
            while (i.hasNext()) {
                i.next();
                QString s=i.key();
                s=s.replace(":","");
                fields += s+"="+i.key()+",";
            }

            fields=   fields.remove(fields.count()-1,1);
            QSqlQuery   query = QSqlQuery(DataHelper::getInstance()->getdb());
            QString queryStr="UPDATE "+ _TableName +" SET "
                    +fields +" where "+whereparams;

            //  qDebug()<<queryStr;

            query.prepare(queryStr);

            QMapIterator<QString, QVariant> j(params);
            while (j.hasNext()) {
                j.next();
                query.bindValue(j.key(),j.value());
            }


            if(query.exec())
            {
                result = true;
            }else
            {
                qDebug()<<query.lastError();
            }
        }
    }
    catch(...)
    {

        DataHelper::lock.unlock();
    }
    DataHelper::lock.unlock();

    return result;
}

bool baseBusiness::Insert( QMap<QString, QVariant> params)
{
    DataHelper::lock.lockForWrite();

    bool result=false;
    try{
        if(DataHelper::getInstance()->dbConnect())
        {
            QSqlQuery   query = QSqlQuery(DataHelper::getInstance()->getdb());
            QString pkey;
            QString pfields;
            QMapIterator<QString, QVariant> i(params);
            while (i.hasNext()) {
                i.next();
                QString str=i.key();
                pfields += str.replace(":","")+",";
                pkey+=i.key()+",";

            }

            pkey=   pkey.remove(pkey.count()-1,1);
            pfields=   pfields.remove(pfields.count()-1,1);
            QString querystr= "INSERT INTO "+ _TableName +
                    " ("+ pfields +")"
                                  " VALUES ("+ pkey + ")";
         //   qDebug()<<querystr;

            query.prepare(querystr);

            //------------set values
            QMapIterator<QString, QVariant> j(params);
            while (j.hasNext()) {
                j.next();
                query.bindValue(j.key(),j.value());
            }

            if(query.exec())
            {
                result = true;
            }else{
                qDebug()<<query.lastError();
            }
        }
    }
    catch(...)
    {

        DataHelper::lock.unlock();
    }
    DataHelper::lock.unlock();

    return result;
}



bool baseBusiness::RemoveAll()
{
    QSqlQuery   query;
    bool result=false;
    DataHelper::lock.lockForRead();

    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            query = QSqlQuery(DataHelper::getInstance()->getdb());
            QString str= "delete  from "+_TableName;

            result=  query.exec(str);
        }
    }
    catch(...)
    {
        qDebug()<<"ERROR";
    }
    DataHelper::lock.unlock();

    return result;
}

bool baseBusiness::RemovebyId(int id)
{
    QSqlQuery   query;
    DataHelper::lock.lockForRead();
    bool result=false;
    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            query = QSqlQuery(DataHelper::getInstance()->getdb());
            QString str= QString("delete  from "+_TableName + "where id = %1").arg(id);
            result=  query.exec(str);
        }
    }
    catch(...)
    {
        qDebug()<<"ERROR";
    }

    DataHelper::lock.unlock();

    return result;
}

bool baseBusiness::Removebywhere(QString whereparams)
{
    QSqlQuery   query;
    DataHelper::lock.lockForRead();
    bool result=false;
    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            query = QSqlQuery(DataHelper::getInstance()->getdb());
            QString str= "delete from "+_TableName + "where "+whereparams;
            result=  query.exec(str);
        }
    }
    catch(...)
    {
        qDebug()<<"ERROR";
    }

    DataHelper::lock.unlock();

    return result;
}

