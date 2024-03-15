#include "EC.h"

EC::CommonParameters EC::getCommonParameters()
{
    CommonParameters params;

    params.curveParams.x = this->ecParams.x;
    params.curveParams.a = this->ecParams.a;
    params.curveParams.b = this->ecParams.b;
    params.curveParams.p = this->ecParams.p;

    params.basePoint = findBasePoint(params.curveParams);

    return params;
}
