#include "datetime.h"
#include "event.h"
#include "calendar.h"
#include "string.h"

#include <iostream>

int main() {
    Datetime d1(2000, 2, 29, 2, 4);
    Datetime d2(2025, 4, 3, 2, 4);
    std::cout << d1 << std::endl << d2 << std::endl << d1-d2 << std::endl;
}