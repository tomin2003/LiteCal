// event.cpp eseménykezelő osztály (definíciók) - SAXHSH

#include "event.h"

/*Értékadás*/

Event& Event::operator=(const Event& rhs)  {
    if (this != &rhs) {
        evDate = rhs.evDate;
        evTime = rhs.evTime;
        evDesc = rhs.evDesc;
    }
    return *this;
}

/*Logikai műveletek*/

bool Event::operator>(const Event& rhs) const {
    return (evDate > rhs.evDate) || (evDate == rhs.evDate && evTime > rhs.evTime);
}

bool Event::operator<(const Event& rhs) const {
    return (evDate < rhs.evDate) || (evDate == rhs.evDate && evTime < rhs.evTime);
}
    
bool Event::operator==(const Event& rhs) const {
    return evDate == rhs.evDate && evTime == rhs.evTime;
}

/*Stream operátorok*/

std::ostream& operator<<(std::ostream& os, const Event& rhs) {
    os << rhs.getEvDate() << ' ' << rhs.getEvTime() << " - " << rhs.getEvDesc();
    return os;
}

std::istream& operator>>(std::istream& is, Event& rhs) {
    Date d;
    Time t;
    char dash;
    // A kötőjel utáni space-t is beleszámítja
    is >> d >> t >> dash >> std::ws;
    // Beolvasás a kötőjelig
    if (is && dash == '-') {
        String s;
        is >> s;
        rhs.setEvDate(d);
        rhs.setEvTime(t);
        rhs.setEvDesc(s);
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}
