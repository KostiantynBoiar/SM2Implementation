#pragma once
#include <string>
#include <iostream>
#include <cmath>

struct GF_p {
    int x, y;
    // Define the equality operator
    bool operator==(const GF_p& other) const {
        return x == other.x && y == other.y;
    }
};

struct ECParams {
    int x, a, b, p;
};
class EC
{

private:

    ECParams ecParams;
    GF_p gfP;
    GF_p findBasePoint(ECParams params) {
        GF_p basePoint;

        while (true) {
            int x = rand() % params.p;
            int y = rand() % params.p;

            if ((y * y) % params.p == (x * x * x + params.a * x + params.b) % params.p) {
                basePoint.x = x;
                basePoint.y = y;
                break;
            }
        }

        return basePoint;
    }

public:
    /*
    function ECAddition()
    function ECMul()
    constructor EC
    */
    EC(int x, int a, int b, int p) {
        this->ecParams.a = a;
        this->ecParams.b = b;
        this->ecParams.p = p;
        this->ecParams.x = x;
        GF_p basePoint = findBasePoint(this->ecParams);
        this->gfP.x = basePoint.x;
        this->gfP.y = basePoint.y;
    }

    ECParams getParams() const {
        return this->ecParams;
    }
    struct CommonParameters {
        ECParams curveParams; // Eliptic Curve Parameters
        GF_p basePoint; // Base point

        friend std::ostream& operator<<(std::ostream& os, const CommonParameters& params) {
            os << "Curve Parameters: x=" << params.curveParams.x << ", a=" << params.curveParams.a << ", b=" << params.curveParams.b << ", p=" << params.curveParams.p << std::endl;
            os << "Base Point: (" << params.basePoint.x << ", " << params.basePoint.y << ")" << std::endl;
            return os;
        }
    };

    CommonParameters getCommonParameters();
    GF_p scalarMultiplication(const GF_p& point, int k);
    GF_p ECAddition(const GF_p& point1, const GF_p& point2);
    std::string generateKey(CommonParameters getCommonParameters);
};
