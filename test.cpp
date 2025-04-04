#include "datetime.h"
#include "event.h"
#include "calendar.h"
#include "string.h"

#include <iostream>

int main() {
    Datetime d1(1970, 1, 1, 0, 0);
    Datetime d2(2090, 12, 31, 23, 59);
    std::cout << d1 << std::endl << d2 << std::endl << d1-d2 << std::endl;

    Datetime d3(2025, 04, 04, 12, 00);
    std::cout << d3 + 6 << std::endl;
}