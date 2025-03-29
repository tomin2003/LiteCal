// date.cpp dátumkezelő osztály (definíciók) - 2025.03.29. SAXHSH

#include "date.h"

// Hány napos egy hónap
const int Date::monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// A hét napjai
const char* Date::weekDays[7] = { {"Hetfo"}, {"Kedd"}, {"Szerda"}, {"Csutortok"}, {"Pentek"}, {"Szombat"}, {"Vasarnap"} };

// getterek inline

// lhs frissebb mint rhs
bool Date::operator>(const Date& rhs) const {
    return (year > rhs.year) || 
           (year == rhs.year && month > rhs.month) || 
           (year == rhs.year && month == rhs.month && day > rhs.day);
}

// lhs régebbi mint rhs
bool Date::operator<(const Date& rhs) const {
    return (year < rhs.year) || 
           (year == rhs.year && month < rhs.month) || 
           (year == rhs.year && month == rhs.month && day < rhs.day);
}

// lhs megegyezik rhs-el
bool Date::operator==(const Date& rhs) const {
    return (year == rhs.year && month == rhs.month && day == rhs.day);
}

