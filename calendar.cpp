// calendar.cpp naptárkezelő osztály (definíciók) - SAXHSH

#include "calendar.h"
#include "event.h"
#include "string.h"
#include "date.h"
#include "time.h"
#include <algorithm>

EventStore::EventStore(const EventStore& rhs) :nEvents(rhs.nEvents), events(new Event[nEvents]) {
    size_t i = 0;
    for (Event &e : *this) {
        e = rhs.events[i++];
    }
    nEvents++;
}

EventStore& EventStore::operator=(const EventStore& rhs) {
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

void EventStore::operator+(const Event& rhs) {
    Event* t_events = new Event[nEvents+1];
    size_t i = 0; 
    for (Event &e : *this) {
        t_events[i++] = e;
    }
    delete[] events;
    t_events[i] = rhs;
    events = t_events;
    nEvents++;
}

void EventStore::sort() {
    std::sort(this->begin(), this->end());
}

size_t EventStore::find(int year = IGNORE, int month = IGNORE, int day = IGNORE, int hour = IGNORE, int minute = IGNORE, String str = IGNORE) {
    
}

std::ostream& operator<<(std::ostream& os, const EventStore& rhs) {
    for (const Event &e : rhs) {
        os << e << std::endl;
    }
    return os;
}
