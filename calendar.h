// calendar.h naptárkezelő osztály (deklarációk, inlineok) - 2025.03.31. SAXHSH

#ifndef CALENDAR_H
#define CALENDAR_H

#include "event.h"
#include "string.h"
#include "date.h"
#include "time.h"

/// @class EventStore
/// A többi (éves, havi) naptár alaposztálya
class EventStore {
private:
    size_t nEvents; ///< események száma
    Event *events; ///< események dinamikus tömbje
public:
/// @brief Default konstruktor
    EventStore() : nEvents(0), events(new Event[0]) {}
    
    /// @brief Paraméteres konstruktor
    /// @param event Egy esemény
    EventStore(const Event& event);

    /// @brief Másoló konstruktor
    /// @param rhs Másolt objektum
    EventStore(const EventStore& rhs);
    
    /// @brief Értékadó operátor
    /// @param rhs Átadott érték
    EventStore& operator=(const EventStore& rhs);

    /// @brief Destruktor (virtuális)
    virtual ~EventStore() { 
        delete[] events;
    }

    /// @brief Iterátor kezdete
    /// @return Első esemény pointer
    Event *begin() { return events; }

    // @brief Iterátor kezdete (konstans)
    /// @return Első esemény pointer
    const Event *begin() const { return events; }

    /// @brief Iterátor vége
    /// @brief Utolsó esemény utáni pointer
    Event *end() { return events + nEvents; }

    /// @brief Iterátor vége
    /// @brief Utolsó esemény utáni pointer
    const Event *end() const { return events + nEvents; }

    /// @brief Az eseményeket sorba rendező függvény
    /// A standard library sort függvényét alkalmazza az események tömbjére.
    void sort();
    
    /// @brief Naptárt kiíró függvény
    /// A származtatott naptárosztályok használják
    //virtual void printCalendar();
};

class MonthlyCalendar :public EventStore {
private:
    int selMonth;
public:
    MonthlyCalendar() :selMonth(0) {}
    MonthlyCalendar(int selMonth) :selMonth(selMonth) {}
    void printCalendar();
};
    
class YearlyCalendar :public EventStore {
private:
    MonthlyCalendar m[12];
    int selYear;
public:
    YearlyCalendar(int selYear) :selYear(selYear) {}
    void printCalendar();
};

#endif