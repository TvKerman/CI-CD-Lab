#include "BigInt.h"
#include <iostream>

int main() {
    BigInt a("9999999999999999999999");
    BigInt b(2);

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;

    return 0;
}
