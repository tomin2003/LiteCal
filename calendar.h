// calendar.h naptárkezelő osztály (deklarációk, inlineok) - 2025.03.31. SAXHSH

#ifndef CALENDAR_H
#define CALENDAR_H

#include "event.h"
#include "string.h"
#include "datetime.h"

/// @class Calendar
/// A többi (éves, havi) naptár alaposztálya
class Calendar {
private:
    Event* events; ///< események dinamikus tömbje
    size_t nEvents; ///< események száma
public:
    Calendar() :events(new Event) {}

    ~Calendar() { delete[] events; }

    void radixSort();
    void binSearch();
    virtual void printCalendar() = 0;
};

#endif

