#include <iostream>
#include "EC.h"

int main() {
    EC ec(1, 2, 3, 17); 
    EC::CommonParameters params = ec.getCommonParameters(); 
    std::cout << params; 
    return 0;
}