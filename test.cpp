#include "datetime.h"

#include <iostream>

int main() {
    Datetime d1(2000, 2, 3, 2, 4);
    Datetime d2(2000, 3, 1, 2, 4);
    std::cout << d1 << std::endl << d2 << std::endl << d1-d2;
}