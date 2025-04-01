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
    Calendar() : events(nullptr), nEvents(0) {}

    /// @brief Destruktor
    /// Virtuális
    virtual ~Calendar() { 
        delete[] events;
        events = nullptr; 
    }

    /// @brief Iterátor osztály
    class Iterator {
        friend class Calendar;
    private:
        Event *it; ///< Esemény pointer

        /// @brief Privát konstruktor
        explicit Iterator(Event *it) : it(it) {}

    public:
        /// @brief Másoló konstruktor
        Iterator(const Iterator& rhs) : it(rhs.it) {}

        /// @brief Értékadó operátor
        /// @param rhs Az értékadás jobboldala
        /// @return Megváltozott értékű *this pointer
        Iterator& operator=(const Iterator& rhs) {
            it = rhs.it;
            return *this;
        }

        /// @brief Összehasonlító operátor
        /// @param rhs Jobboldali iterátor objektum
        /// @return megegyeznek-e az iterátorok
        bool operator==(const Iterator& rhs) const {
            return it == rhs.it;
        }

        /// @brief Összehasonlító operátor
        /// @param rhs Jobboldali iterátor objektum
        /// @return nem-e egyezik meg a két iterátor
        bool operator!=(const Iterator& rhs) const {
            return it != rhs.it;
        }

        /// @brief Dereferencia operátor
        /// @return Aktuális esemény
        Event& operator*() {
            return *it;
        }

        /// @brief Dereferencia operátor (konstans)
        /// @return Aktuális esemény
        const Event& operator*() const {
            return *it;
        }  

        /// @brief Nyíl operátor az adattagok közvetlen hozzáférésére
        /// @return Közvetlen elért adattag
        Event* operator->() {
            return it;
        }

        /// @brief Nyíl operátor az adattagok közvetlen hozzáférésére (konstans)
        /// @return Közvetlen elért adattag
        const Event* operator->() const {
            return it;
        }

        /// @brief Preinkremens operátor
        /// @return inkrementált *this pointer
        Iterator& operator++() {
            ++it;
            return *this;
        }

        /// @brief Posztinkremens operátor
        /// @return inkrementált *this pointer
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    /// @brief Iterátor kezdete
    /// @return Első esemény iterátor
    Iterator begin() { return Iterator(events); }

    /// @brief Iterátor vége
    /// @brief Utolsó esemény utáni iterátor
    Iterator end() { return Iterator(events + nEvents); }

    /// @brief Naptárt kiíró függvény
    /// A származtatott naptárosztályok használják
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

