// time.cpp időkezelő osztály (definíciók) - SAXHSH

#include "time.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

/* Belső információkat megállapító függvények */

bool Time::isValid() const {
    return hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}

/* Logikai összehasonlítások */

bool Time::operator>(const Time& rhs) const {
    if (hour != rhs.hour) return hour > rhs.hour;
    return minute > rhs.minute;
}

bool Time::operator<(const Time& rhs) const {
    if (hour != rhs.hour) return hour < rhs.hour;
    return minute < rhs.minute;
}

bool Time::operator==(const Time& rhs) const {
    return hour == rhs.hour && minute == rhs.minute;
}

bool Time::operator<=(const Time& rhs) const {
    return (*this < rhs) || (*this == rhs);
}

bool Time::operator>=(const Time& rhs) const {
    return (*this > rhs) || (*this == rhs);
}

/* Stream operátorok */

std::ostream& operator<<(std::ostream& os, const Time& rhs) {
    os << std::setfill('0') << std::setw(2) << rhs.getHour() << ':' << std::setfill('0') << std::setw(2) << rhs.getMinute();
    return os;
}

std::istream& operator>>(std::istream& is, Time& rhs) {
    int hour, minute;
    char colon;
    is >> hour >> colon >> minute;
    if (is && colon == ':') {
        try {
            rhs.setHour(hour);
            rhs.setMinute(minute);
        } catch(const invalid_time &e) {
            std::cout << e.what();
            is.setstate(std::ios::failbit); // Hibás beolvasás
        }
    } else {
        is.setstate(std::ios::failbit); // Hibás beolvasás
    }
    return is;
}