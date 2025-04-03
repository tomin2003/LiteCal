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
    return evTime > rhs.evTime;
}

bool Event::operator<(const Event& rhs) {
    return evTime < rhs.evTime;
}

bool Event::operator==(const Event& rhs) {
    return evTime == rhs.evTime;
}