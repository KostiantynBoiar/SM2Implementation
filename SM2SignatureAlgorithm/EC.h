#pragma once
#include <string>
#include <iostream>
#include <cmath>

class EC
{
private:
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
    ECParams ecParams;
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
    EC(const ECParams& ecParams){
        this->ecParams = ecParams;
    }

    struct CommonParameters {
        ECParams curveParams; // Eliptic Curve Parameters
        GF_p basePoint; // Base point
    };

    CommonParameters getCommonParameters();
    GF_p scalarMultiplication(const GF_p& point, int k);
    GF_p ECAddition(const GF_p& point1, const GF_p& point2);
    std::string generateKey(CommonParameters getCommonParameters);
};

