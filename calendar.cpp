// calendar.cpp naptárkezelő osztály (definíciók) - 2025.03.31. SAXHSH

#include "calendar.h"
#include "event.h"
#include "string.h"
#include "datetime.h"
#include <algorithm>

/* Konstruktorok */
/*
Calendar::Calendar(const Calendar& rhs) :nEvents(rhs.nEvents), events(new Event[nEvents]) {
    size_t i = 0;
    for (Event &e : *this) {
        e = rhs.events[i++];
    }
}

Calendar& Calendar::operator=(const Calendar& rhs) {
    if (this != &rhs) {
        delete[] events;
        nEvents = rhs.nEvents;
        events = new Event[nEvents];
        size_t i = 0;
        for (Event &e : *this) {
            e = rhs.events[i++];
        }
    }
    return *this;
}
    */

void Calendar::sort() {
    //std::sort(this->begin(), this->end());
}

std::ostream& operator<<(std::ostream& os, const Event& rhs){
    os << rhs.getEvTime() << ' ' <<rhs.getEvDesc();
    return os;
}
