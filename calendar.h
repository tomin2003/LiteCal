// calendar.h naptárkezelő osztály (deklarációk, inlineok) - 2025.03.31. SAXHSH

#ifndef CALENDAR_H
#define CALENDAR_H

#include "event.h"
#include "string.h"
#include "datetime.h"


    

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

/// @class Calendar
/// A többi (éves, havi) naptár alaposztálya
class Calendar {
private:
    size_t nEvents; ///< események száma
    Event *events; ///< események dinamikus tömbje
public:
    /// @brief Default konstruktor
    Calendar() : nEvents(0), events(new Event[0]) {}

    /// @brief Paraméteres konstruktor
    /// @param event Egy esemény
    Calendar(const Event& event);

    /// @brief Másoló konstruktor
    /// @param rhs Másolt objektum
    Calendar(const Calendar& rhs);

    /// @brief Értékadó operátor
    /// @param rhs Átadott érték
    Calendar& operator=(const Calendar& rhs);

    /// @brief Destruktor (virtuális)
    virtual ~Calendar() { 
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
    virtual void printCalendar();
};