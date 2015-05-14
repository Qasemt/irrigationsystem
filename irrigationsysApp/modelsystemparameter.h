#ifndef MODELSYSTEMPARAMETER_H
#define MODELSYSTEMPARAMETER_H
#include <QString>

class ModelSystemParameter
{
public:
    ModelSystemParameter():pkey(0),pkeytitle(""),pvalue("")
    {

    }

    int pkey    ;
    QString pkeytitle;
    QString pvalue;

    int getPkey() const;
    void setPkey(int value);
    QString getPkeytitle() const;
    void setPkeytitle(const QString &value);
    QString getPvalue() const;
    void setPvalue(const QString &value);
};


#endif // MODELSYSTEMPARAMETER_H
