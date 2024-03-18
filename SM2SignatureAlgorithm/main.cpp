#include <iostream>
#include "EC.h"

int main() {
    EC ec(123, 2123123, 3232323, 4123123, 120); 
    EC::CommonParameters params = ec.getCommonParameters(); 
    std::cout << params; 
    GF_p secondCurve;
    secondCurve.x = 1;
    secondCurve.y = 5;
    GF_p addition = ec.scalarMultiplication(secondCurve, 101);
    std::cout << addition.x << " " << addition.y;
    return 0;
}