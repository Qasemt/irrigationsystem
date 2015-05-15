#ifndef MODELSYSTEMPARAMETER_H
#define MODELSYSTEMPARAMETER_H
#include <QString>

class ModelSystemParameter
{
private:
    int pkey    ;
    QString pkeytitle;
    QString pvalue;
public:
    ModelSystemParameter():pkey(0),pkeytitle(""),pvalue("")
    {

    }



    int getPkey() const;
    void setPkey(int value);
    QString getPkeytitle() const;
    void setPkeytitle(const QString &value);
    QString getPvalue() const;
    void setPvalue(const QString &value);
};


#endif // MODELSYSTEMPARAMETER_H
