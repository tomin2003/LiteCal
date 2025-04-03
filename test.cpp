#include "datetime.h"
#include "event.h"
#include "calendar.h"
#include "string.h"

#include <iostream>

int main() {
    Datetime d1(2000, 2, 3, 2, 4);
    Datetime d2(2025, 4, 3, 2, 4);
    std::cout << d1 << std::endl << d2 << std::endl << d1-d2 << std::endl;

    Event e1(d1, "régi");
    Event e2(d2, "új");
    std::cout << e1 << std::endl;
    std::cout << e2.getEvTime().getWeekDay();
    std::cout << e2 > e1;
}