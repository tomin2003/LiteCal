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
    Event e2(1999, 1, 29, 12, 00, "hay");
    std::cout << d1 << std::endl << d2 << std::endl << d1-d2 << std::endl;
    //std::cout << e1 << std::endl;

    EventStore es(e1);
    es+e2;
    es.list();
    es.sort();
    std::cout << es;
}