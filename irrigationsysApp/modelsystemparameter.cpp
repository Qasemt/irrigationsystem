#include "modelsystemparameter.h"


QString ModelSystemParameter::getPvalue() const
{
    return pvalue;
}

void ModelSystemParameter::setPvalue(const QString &value)
{
    pvalue = value;
}

QString ModelSystemParameter::getPkeytitle() const
{
    return pkeytitle;
}

void ModelSystemParameter::setPkeytitle(const QString &value)
{
    pkeytitle = value;
}

int ModelSystemParameter::getPkey() const
{
    return pkey;
}

void ModelSystemParameter::setPkey(int value)
{
    pkey = value;
}

