// time.cpp időkezelő osztály (definíciók) - 2025.04.08. SAXHSH

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

//

std::ostream& operator<<(std::ostream& os, const Time& rhs) {
    os << std::setfill('0') << std::setw(2) << rhs.getHour() << ':' << std::setfill('0') << std::setw(2) << rhs.getMinute();
    return os;
}