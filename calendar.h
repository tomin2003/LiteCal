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
    Event *events; ///< események dinamikus tömbje
    size_t nEvents; ///< események száma
public:
    /// @brief Default konstruktor
    Calendar() :events(new Event) {}

    /// @brief Destruktor
    /// Virtuális
    virtual ~Calendar() { delete[] events; }

    /// @brief Iterátor (az osztályon belül)
    class Iterator {
        private:
            Event *ptr;
        public:
            Iterator(Event *p) : ptr(p) {}
            
    };

    virtual void printCalendar() = 0;
};

class monthlyCalendar : public Calendar {
private:
    int selMonth;
public:
    monthlyCalendar(int selMonth) :selMonth(selMonth) {}
    void printCalendar();
};

class yearlyCalendar : public Calendar {
private:
    int selYear;
public:
    yearlyCalendar(int selYear) :selYear(selYear) {}
    void printCalendar();
};

#endif

