#include <iostream>
#include "SM2.h"
#include <utility>

int main() {
	SM2 sm2(2, 2, 2, 2, 2, 2, 2);
	std::pair <int, int> key = sm2.generateKey();
	std::cout << key.first << " " << key.second;
	return 0;
}