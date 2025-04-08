// calendar.cpp naptárkezelő osztály (definíciók) - 2025.03.31. SAXHSH

#include "calendar.h"
#include "event.h"
#include "string.h"
#include "date.h"
#include "time.h"
#include <algorithm>

/* Konstruktorok */
/*
EventStore::EventStore(const EventStore& rhs) :nEvents(rhs.nEvents), events(new Event[nEvents]) {
    size_t i = 0;
    for (Event &e : *this) {
        e = rhs.events[i++];
    }
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
    */

void EventStore::sort() {
    //std::sort(this->begin(), this->end());
}

