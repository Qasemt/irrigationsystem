#include "bssystemparameter.h"

Bssystemparameter::Bssystemparameter()
{
}


ModelSystemParameter Bssystemparameter::GetValueParam(eParamKeys key)
{
    DataHelper::lock.lockForRead();
    ModelSystemParameter res;
    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            QSqlQuery   query = QSqlQuery(DataHelper::getInstance()->getdb());

            QString str= "select * from systemparameter  where pkey = " +QString::number((int)key);

            query.exec(str);

            while (query.next())
            {
                res=  fromSqlQuery(query);
            }
            // SqlConnection::getInstance()->dbDisconnect();
        }
    }
    catch(...)
    {
        qDebug()<<"Bssystemparameter - GetValueParam - has been error";
    }
    DataHelper::lock.unlock();

    return res;
}

ModelSystemParameter Bssystemparameter::fromSqlQuery(QSqlQuery query)
{
    ModelSystemParameter mdl ;
    mdl.setPkey(query.value(query.record().indexOf("pkey")).toInt());
    mdl.setPkeytitle(query.value(query.record().indexOf("pkeytitle")).toString());
    mdl.setPvalue(query.value(query.record().indexOf("pvalue")).toString());

    return mdl;
}

QList<ModelSystemParameter> Bssystemparameter::FillData()
{
    QSqlQuery   query;
    DataHelper::lock.lockForRead();
    QList<ModelSystemParameter> tmplist;
    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            query = QSqlQuery(DataHelper::getInstance()->getdb());
            QString str= "select * from systemparameter";

            query.exec(str);
            while (query.next())
            {
                ModelSystemParameter md= fromSqlQuery(query);
                tmplist.append(md);
            }


        }
    }
    catch(...)
    {
        qDebug()<<"ERROR";
    }
    DataHelper::lock.unlock();

    return tmplist;

}

bool Bssystemparameter::Update(int key, QString title, QString value)
{
    if(title.isEmpty() || value.isEmpty()) return false;

    DataHelper::lock.lockForWrite();

    bool result=false;
    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            QSqlQuery   query = QSqlQuery(DataHelper::getInstance()->getdb());
            query.prepare(QString("UPDATE systemparameter SET pkey=%1,pkeytitle=:title,pvalue=:val WHERE pkey = :kkey;").arg(key));


            query.bindValue(":kkey",QString::number(key));
            query.bindValue(":title",title);
            query.bindValue(":val",value);

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

bool Bssystemparameter::Insert(int key, QString title, QString value)
{
    if(key<=0) return false;

    if(title.isEmpty() || value.isEmpty()) return false;

    DataHelper::lock.lockForWrite();

    bool result=false;
    try{

        if(DataHelper::getInstance()->dbConnect())
        {
            QSqlQuery   query = QSqlQuery(DataHelper::getInstance()->getdb());
            query.prepare("INSERT INTO systemparameter(pkey,pkeytitle,pvalue"
                          " VALUES (:key,:title,:val)");

            query.bindValue(":key",key);
            query.bindValue(":title",title);
            query.bindValue(":val",value);

            if(query.exec())
            {
                result = true;
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
