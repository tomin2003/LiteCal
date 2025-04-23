// event.cpp eseménykezelő osztály (definíciók) - SAXHSH

#include "event.h"

Event& Event::operator=(const Event& rhs)  {
    if (this != &rhs) {
        evDate = rhs.evDate;
        evTime = rhs.evTime;
        evDesc = rhs.evDesc;
    }
    return *this;
}

bool Event::operator>(const Event& rhs) {
    return evDate > rhs.evDate && evTime > rhs.evTime;
}

bool Event::operator<(const Event& rhs) {
    return evDate < rhs.evDate && evTime < rhs.evTime;
}

bool Event::operator==(const Event& rhs) {
    return evDate == rhs.evDate && evTime == rhs.evTime;
}

std::ostream& operator<<(std::ostream& os, const Event& rhs) {
    os << rhs.getEvDate() << ' ' << rhs.getEvTime() << " - " << rhs.getEvDesc();
    return os;
}