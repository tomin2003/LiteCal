// calendar.cpp naptárkezelő osztály (definíciók) - SAXHSH

#include "calendar.h"
#include "event.h"
#include "string.h"
#include "date.h"
#include "time.h"
#include "except.h"
#include <algorithm>

/* Másoló konstruktor */

EventStore::EventStore(const EventStore& rhs): nEvents(rhs.nEvents), events(new Event[nEvents]) {
    for (size_t i = 0; i < nEvents; i++) {
        events[i] = rhs.events[i];
    }
}

/* Értékadó operátor */

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

Event& EventStore::operator[](int i) {
    if (i < 0 || i >= static_cast<int>(nEvents)) throw std::out_of_range ("Túlindexelted az eseménytárolót!");
    return events[i];
}

Event EventStore::operator[](int i) const {
    if (i < 0 || i >= static_cast<int>(nEvents)) throw std::out_of_range ("Túlindexelted az eseménytárolót!");
    return events[i];
}

Event& EventStore::find(const Event& searchCrit) {
    auto it = std::find(this->begin(), this->end(), searchCrit);
    if (it == this->end()) throw nofind("Az esemény nem található.");
    return *it;
 }

const Event& EventStore::find(const Event& searchCrit) const {
   auto it = std::find(this->begin(), this->end(), searchCrit);
   if (it == this->end()) throw nofind("Az esemény nem található.");
   return *it;
}

void EventStore::eventClash(const Event& checked) const {
    for (const Event &e : *this) {
        if (e.getEvDate() == checked.getEvDate() && e.getEvTime() == checked.getEvTime()) {
            throw evclash("A listában már szerepel azonos dátumú és idejű esemény.");
        }
    }
}

EventStore& EventStore::operator+(const Event& rhs) {
    eventClash(rhs);
    Event* t_events = new Event[nEvents+1];
    size_t i = 0; 
    for (Event &e : *this) {
        t_events[i++] = e;
    }
    delete[] events;
    t_events[i] = rhs;
    events = t_events;
    nEvents++;
    return *this;
}

EventStore& EventStore::operator-(const Event& rhs) {
    Event& found = find(rhs);
    Event* t_events = new Event[nEvents-1];
    size_t i = 0;
    for (Event& e : *this) {
        if (e == found) continue;
        t_events[i++] = e;
    }
    delete[] events;
    events = t_events;
    nEvents--;
    return *this;
}

void EventStore::sort() {
    std::sort(this->begin(), this->end());
}

std::ostream& operator<<(std::ostream& os, const EventStore& rhs) {
    for (const Event &e : rhs) {
        os << e << "\n";
    }
    return os;
}
