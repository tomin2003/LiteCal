// calendar.cpp naptárkezelő osztály (definíciók) - SAXHSH

#include "calendar.h"
#include "event.h"
#include "string.h"
#include "date.h"
#include "time.h"
#include "except.h"
#include <algorithm>
#include <iomanip>

/*Másoló konstruktor*/

EventStore::EventStore(const EventStore& rhs): nEvents(rhs.nEvents), events(new Event[nEvents]) {
    for (size_t i = 0; i < nEvents; i++) {
        events[i] = rhs.events[i];
    }
}

/*Értékadó operátor*/

EventStore& EventStore::operator=(const EventStore& rhs) {
    if (this != &rhs) {
        delete[] events;
        nEvents = rhs.nEvents;
        events = new Event[nEvents];
        for (size_t i = 0; i < nEvents; ++i) {
            events[i] = rhs.events[i];
        }
    }
    return *this;
}

/*Indexelő operátorok*/

Event& EventStore::operator[](int i) {
    if (i < 0 || i >= static_cast<int>(nEvents)) {
        throw std::out_of_range ("Túlindexelted az eseménytárolót!");
    }
    return events[i];
}

Event EventStore::operator[](int i) const {
    if (i < 0 || i >= static_cast<int>(nEvents)) {
        throw std::out_of_range ("Túlindexelted az eseménytárolót!");
    }
    return events[i];
}

/*Keresés*/

Event& EventStore::find(const Event& searchEv) {
    auto it = std::find(this->begin(), this->end(), searchEv);
    if (it == this->end()) {
        throw nofind("Az esemény nem található.");
    }
    return *it;
 }

const Event& EventStore::find(const Event& searchEv) const {
   auto it = std::find(this->begin(), this->end(), searchEv);
   if (it == this->end()) {
       throw nofind("Az esemény nem található.");
   }
   return *it;
}

Event& EventStore::find(const Date& searchDate) {
    auto it = std::find_if(this->begin(), this->end(), [&searchDate](const Event& e) {
        return e.getEvDate() == searchDate;
    });
    if (it == this->end()) {
        throw nofind("Az esemény nem található.");
    }
    return *it;
 }

const Event& EventStore::find(const Date& searchDate) const {
    auto it = std::find_if(this->begin(), this->end(), [&searchDate](const Event& e) {
        return e.getEvDate() == searchDate;
    });
    if (it == this->end()) {
        throw nofind("Az esemény nem található.");
    }
    return *it;
 }

 Event& EventStore::find(const Time& searchTime) {
    auto it = std::find_if(this->begin(), this->end(), [&searchTime](const Event& e) {
        return e.getEvTime() == searchTime;
    });
    if (it == this->end()) {
        throw nofind("Az esemény nem található.");
    }
    return *it;
 }

const Event& EventStore::find(const Time& searchTime) const {
    auto it = std::find_if(this->begin(), this->end(), [&searchTime](const Event& e) {
        return e.getEvTime() == searchTime;
    });
    if (it == this->end()) {
        throw nofind("Az esemény nem található.");
    }
    return *it;
 }

 Event& EventStore::find(const String& searchDesc) {
    auto it = std::find_if(this->begin(), this->end(), [&searchDesc](const Event& e) {
        return e.getEvDesc() == searchDesc;
    });
    if (it == this->end()) {
        throw nofind("Az esemény nem található.");
    }
    return *it;
 }

const Event& EventStore::find(const String& searchDesc) const {
    auto it = std::find_if(this->begin(), this->end(), [&searchDesc](const Event& e) {
        return e.getEvDesc() == searchDesc;
    });
    if (it == this->end()) {
        throw nofind("Az esemény nem található.");
    }
    return *it;
 }

/*Szűrés*/

EventStore EventStore::filterBy(int year, int month, int day) {
    EventStore filteredStore;

    for (const Event& e : *this) {
        const auto& date = e.getEvDate();

        bool match = true;
        if (date.getYear() != year) match = false;
        if (month != NOPARAM && date.getMonth() != month) match = false;
        if (day != NOPARAM && date.getDay() != day) match = false;
        if (match) {
            filteredStore + e;
        }
    }
    return filteredStore;
}

const EventStore EventStore::filterBy(int year, int month, int day) const {
    EventStore filteredStore;

    for (const Event& e : *this) {
        const auto& date = e.getEvDate();

        bool match = true;
        if (date.getYear() != year) match = false;
        if (month != NOPARAM && date.getMonth() != month) match = false;
        if (day != NOPARAM && date.getDay() != day) match = false;
        if (match) {
            filteredStore + e;
        }
    }
    return filteredStore;
}

/*Eseményütközés*/

void EventStore::eventClash(const Event& checked) const {
    for (const Event &e : *this) {
        if (e.getEvDate() == checked.getEvDate() && e.getEvTime() == checked.getEvTime()) {
            throw evclash("A listában már szerepel azonos dátumú és idejű esemény.");
        }
    }
}

/*Hozzáfűzés, kitörlés*/

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

/*Rendezés*/

void EventStore::sort() {
    std::sort(this->begin(), this->end());
}

/*Stream operátor*/

std::ostream& operator<<(std::ostream& os, const EventStore& rhs) {
    for (const Event &e : rhs) {
        os << e << "\n";
    }
    return os;
}

void MonthlyCalendar::printCalendar(std::ostream& os) {
    using namespace std; // sokszor kéne kiírni, itt a függvényen belül nem lesz baj belőle
    // fejléc
    os << "\t\t     " << selYear << ". " << setw(2) << setfill('0') << selMonth << '.' << endl;
    for (int i = 0; i < 52; i++) {
        os << '-';
    }  
    os << endl;
    os << " Hé\t Ke\t Sze\t Csü\t Pén\t Szo\t Vas" << endl;
    // kiinduló dátum - ebből lehet meghatározni a kezdőnapját a hétnek
    Date baseline(selYear, selMonth, 1);
    int weekDayIdx = baseline.getWeekDayIdx();
    // a végdátumot itt kezeljük le
    int maxdays = baseline.daysInMonth(selMonth);
    int offset; // és a kezdőnep segítségével eltolni
    for (offset = 0; offset < weekDayIdx; offset++) {
        os << '\t';
    }
    for (int day = 1; day <= maxdays; day++) {
        os << ' ' << setw(2) << setfill(' ') << day;
        // Találja meg azt a napot, amely napon van esemény 
        // a find() nem boolt ad vissza, kivételt is dob, nem ideális!
        for (int j = 0; j < static_cast<int>(nEvents); j++) {
            if (events[j].getEvDate().getDay() == day) {
                os << '*'; // megjelöli azokat a napokat, amiken van esemény
            }
        }
        // Egy sorban max 7 nap, utána új sor
        ((day+offset) % 7 == 0)?(os << '\n'):(os << '\t');
    }
    os << '\n';
}

void YearlyCalendar::printCalendar(std::ostream& os) {
    using namespace std; // sokszor kéne kiírni, itt a függvényen belül nem lesz baj belőle
    // 12 db hónap egymásutánja
    for (int month = 1; month <= 12; month++) {
        std::stringstream ss;
        MonthlyCalendar temp(*this, selYear, month);
        temp.printCalendar(ss);
        os << ss.str();
        for (int i = 0; i < 52; i++) {
            os << '-';
        }  
        os << "\n\n";
    }
}

