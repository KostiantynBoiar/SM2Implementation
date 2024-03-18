﻿#include "EC.h"

EC::CommonParameters EC::getCommonParameters()
{
    CommonParameters params;

    params.curveParams = this->getParams();
    params.basePoint = findBasePoint(this->getParams());

    return params;
}

GF_p EC::scalarMultiplication(const GF_p& point, int k)
{
    GF_p result;
    result.x = point.x;
    result.y = point.y;

    for (int i = 1; i < k; ++i) {
        result = ECAddition(result, point);
    }

    return result;
}

GF_p EC::ECAddition(const GF_p& point1, const GF_p& point2)
{
    GF_p result;

    if (point1.x == point2.x && point1.y != point2.y) {
        result.x = 0;
        result.y = 0;
        return result; // Операция неопределена - точки на разных касательных
    }
    if (point1.x == 0 && point2.y == 0) {
        return point2;
    }
    if(point2.x == 0 && point2.y == 0){
        return point1;
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

int* EC::findSlopeOfTwoPoints(int x1, int y1, int x2, int y2)
{

   
}

void EC::negate()
{
    this->gfP.y = -(this->gfP.y);
}


std::string EC::generateKey(CommonParameters getCommonParameters)
{
    return std::string();
}