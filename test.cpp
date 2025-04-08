#include "date.h"
#include "time.h"
#include "event.h"
#include "calendar.h"
#include "string.h"

#include <iostream>

int main() {
    Date d1(1970, 1, 1);
    Date d2(2100, 12, 31);
    Event e1(2000, 2, 29, 16, 00, "heyho");
    std::cout << d1 << std::endl << d2 << std::endl << d1-d2 << std::endl;
    std::cout << e1 << std::endl;
}