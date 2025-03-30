// date.cpp dátumkezelő osztály (definíciók) - 2025.03.29. SAXHSH

#include "date.h"
#include <cstddef>
#include <cmath>
#include <stdexcept>

/* Statikus adattag definíciók */

const int Date::monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const char* Date::weekDays[7] = { {"Szombat"}, {"Vasarnap"}, {"Hetfo"}, {"Kedd"}, {"Szerda"}, {"Csutortok"}, {"Pentek"} };

/* Getterek definíciója a headerben */

/* Belső információkat megállapító függvények */

bool Date::isLeapYear() const {
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

bool Date::isValid() const {
    if (month < 1 || month > 12 || year < 1900) return false;

    int maxDays = monthDays[month - 1];
    if (month == 2 && isLeapYear()) maxDays = 29;
    return day >= 1 && day <= maxDays;
}

const char* Date::getWeekDay() const {
    // Zeller's Congruence
    if (!isValid()) throw std::invalid_argument("Érvénytelen dátum!");
    size_t q = day; // nap
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
    size_t h = (q+(13*(m+1)/5)+K+K/4+J/4-2*J) % 7;
    return weekDays[h];
}

/* Logikai összehasonlítások */

bool Date::operator>(const Date& rhs) const {
    return (year > rhs.year) || 
           (year == rhs.year && month > rhs.month) || 
           (year == rhs.year && month == rhs.month && day > rhs.day);
}

bool Date::operator<(const Date& rhs) const {
    return (year < rhs.year) || 
           (year == rhs.year && month < rhs.month) || 
           (year == rhs.year && month == rhs.month && day < rhs.day);
}

bool Date::operator==(const Date& rhs) const {
    return (year == rhs.year && month == rhs.month && day == rhs.day);
}