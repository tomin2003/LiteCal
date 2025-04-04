// datetime.cpp dátum és időkezelő osztály (definíciók) - 2025.03.31. SAXHSH

#include "datetime.h"
#include <iostream>
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <iomanip>

/* Statikus adattag definíció */

const char* Datetime::weekDays[7] = { {"Szombat"}, {"Vasarnap"}, {"Hetfo"}, {"Kedd"}, {"Szerda"}, {"Csutortok"}, {"Pentek"} };

/* Getterek definíciója a headerben */

/* Belső információkat megállapító függvények */

bool Datetime::isLeapYear() const {
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

bool Datetime::isLeapYear(int y) const {
    return (y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

int Datetime::daysInMonth(int m) const {
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (m == 2 && isLeapYear()) ? 29 : monthDays[m-1];
}

bool Datetime::isValid() const {
    return (year >= 1970 && year <= 2100) && (month >= 1 && month <= 12) && 
    (day >= 1 && day <= daysInMonth(month)) && (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}

const char* Datetime::getWeekDay() const {
    // Zeller's Congruence
    size_t m = month; // hónap
    size_t y = year; // év
    // hónapok: 3 = március, 4 = április, ..., 14 = február 
    if (m < 3) {
        m += 12;
        y--;
    }
    size_t K = y % 100; // évszázad-beli év
    size_t J = y / 100; // évszázad
    // Képlet
    size_t q = day; // nap
    size_t h = (q+(13*(m+1)/5)+K+K/4+J/4-2*J) % 7;
    return weekDays[h];
}

int Datetime::dateInDays() const {
    int days = day;
    for (int i = 1; i <= month; i++) {
        days += daysInMonth(i);
    }
    for (int i = 1970; i < year; i++) {
        // Itt van felhasználva a felüldefiniált isLeapYear(int) felhasználva
        days += (isLeapYear(i) ? 366 : 365);
    }
    return days;
}

/* Logikai összehasonlítások */

bool Datetime::operator>(const Datetime& rhs) const {
    if (year != rhs.year) return year > rhs.year;
    if (month != rhs.month) return month > rhs.month;
    if (day != rhs.day) return day > rhs.day;
    if (hour != rhs.hour) return hour > rhs.hour;
    return minute > rhs.minute;
}

bool Datetime::operator<(const Datetime& rhs) const {
    if (year != rhs.year) return year < rhs.year;
    if (month != rhs.month) return month < rhs.month;
    if (day != rhs.day) return day < rhs.day;
    if (hour != rhs.hour) return hour < rhs.hour;
    return minute > rhs.minute;
}


bool Datetime::operator==(const Datetime& rhs) const {
    return year == rhs.year && month == rhs.month && day == rhs.day && hour == rhs.hour && minute == rhs.minute;
}

bool Datetime::operator<=(const Datetime& rhs) const {
    return (*this < rhs) || (*this == rhs);
}

bool Datetime::operator>=(const Datetime& rhs) const {
    return (*this > rhs) || (*this == rhs);
}

Datetime Datetime::operator+(int rhs) const {
    int y = year;
    int m = month;
    int d = day + rhs;
    while (d > daysInMonth(m)) {
        m++;
        d -= daysInMonth(m);
        if (m > 12) {
            m = 1;
            y++;
        }
    }
    return Datetime(y, m, d, hour, minute);
}

int Datetime::operator-(const Datetime& rhs) const {
    return abs(dateInDays()-rhs.dateInDays());
}


std::ostream& operator<<(std::ostream& os, const Datetime& rhs) {
    os << rhs.getYear() << ". " << std::setfill('0') << std::setw(2) << rhs.getMonth() << ". " << std::setw(2) 
    << rhs.getDay() << ". " << std::setw(2) << rhs.getHour() << ':' << std::setw(2) << rhs.getMinute();
    return os;
}