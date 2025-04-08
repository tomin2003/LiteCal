// event.cpp eseménykezelő osztály (definíciók) - 2025.04.03. SAXHSH

#include "event.h"

Event& Event::operator=(const Event& rhs)  {
    if (this != &rhs) {
        evTime = rhs.evTime;
        evDesc = rhs.evDesc;
    }
    return *this;
}

bool Event::operator>(const Event& rhs) {
    return evDate > rhs.evDate;
}

bool Event::operator<(const Event& rhs) {
    return evDate < rhs.evDate;
}

bool Event::operator==(const Event& rhs) {
    return evDate == rhs.evDate;
}

std::ostream& operator<<(std::ostream& os, const Event& rhs) {
    os << rhs.getEvDate() << ' ' << rhs.getEvTime() << " - " << rhs.getEvDesc();
    return os;
}