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

EC::GF_p EC::scalarMultiplication(const GF_p& point, int k)
{
    GF_p result;
    result.x = point.x;
    result.y = point.y;

    for (int i = 1; i < k; ++i) {
        result = ECAddition(result, point);
    }

    return result;
}

EC::GF_p EC::ECAddition(const GF_p& point1, const GF_p& point2)
{
    GF_p result;

    if (point1.x == point2.x && point1.y != point2.y) {
        result.x = 0;
        result.y = 0;
        return result; // Операция неопределена - точки на разных касательных
    }

    int lambda;
    if (point1 == point2) { // Если точки равны, используем производную
        lambda = (3 * point1.x * point1.x + this->ecParams.a) * pow(2 * point1.y, -1);
    }
    else {
        lambda = (point2.y - point1.y) * pow(point2.x - point1.x, -1);
    }

    result.x = (lambda * lambda - point1.x - point2.x) % this->ecParams.p;
    result.y = (lambda * (point1.x - result.x) - point1.y) % this->ecParams.p;

    return result;
}


std::string EC::generateKey(CommonParameters getCommonParameters)
{
    return std::string();
}
