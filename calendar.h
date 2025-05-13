// calendar.h naptárkezelő osztály (deklarációk, inlineok) - SAXHSH
#ifndef CALENDAR_H
#define CALENDAR_H

#include "event.h"
#include "string.h"
#include "date.h"
#include "time.h"

/// @class EventStore
/// A többi (éves, havi) naptár alaposztálya
class EventStore {
protected:
    size_t nEvents; ///< események száma
    Event *events; ///< események dinamikus tömbje
public:
/// @brief Default konstruktor
    EventStore() :nEvents(0), events(new Event[0]) {}
    
    /// @brief Paraméteres konstruktor
    /// @param event Egy esemény
    EventStore(const Event& event) :nEvents(1), events(new Event[1]) { events[0] = event; }

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

    /// @brief Getter függvény  
    /// @return Tároló
    Event* getEvents() { return events; }
    
    /// @brief Getter függvény
    /// @return Tárolt semények száma
    size_t getNEvents() { return nEvents; };

    /// @brief Indexelő operátor
    /// Módosíthatja a hívó objektumot. Végez indexellenőrzést, kivétellel tér vissza érvénytelen indexelés esetén.
    /// @param i index
    /// @return indexelt elem referenciája
    Event& operator[](int i);
    
    /// @brief Indexelő operátor
    /// NEM módosíthatja a hívó objektumot. Végez indexellenőrzést, kivétellel tér vissza érvénytelen indexelés esetén.
    /// @param i index
    /// @return indexelt elem értéke
    Event operator[](int i) const;

    /// @brief Kereső függvény az eseménytárolóban.
    /// @param searchCrit Az esemény ami a keresés kritériuma
    /// @return Az esemény referenciája (ha nincs találat, akkor except::nofind kivételt dob)
    Event& find(const Event& searchCrit);
    
    /// @brief Kereső függvény az eseménytárolóban.
    /// @param searchCrit Az esemény ami a keresés kritériuma
    /// @return Az esemény referenciája (konstans) (ha nincs találat, akkor except::nofind kivételt dob)
    const Event& find(const Event& searchCrit) const;

    /// @brief Kivételt dob (except::evclash) ha a listában van a vizsgálttal ütköző esemény.
    /// @param checked Vizsgált esemény
    void eventClash(const Event& checked) const;

    /// @brief Az események listájához hozzáfűz egy új eseményt.
    /// @param rhs A hozzáfűzött esemény
    /// @return *this pointer
    EventStore& operator+(const Event& rhs);

    /// @brief Az események listájából töröl egy specifikus eseményt.
    /// @param rhs A törlendő esemény
    /// @return *this pointer
    EventStore& operator-(const Event& rhs);
    
    /// @brief Az események listájt dátum szerint csökkenő sorrendbe rendezi.
    /// Ehhez az std::sort() STL függvényt használja.
    void sort();

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
};

/// @brief Az eseményeket kiíró operátor
/// @param os output stream
/// @param rhs eseménytömb
/// @return output stream
std::ostream& operator<<(std::ostream& os, const EventStore &rhs);

// Ennek a résznek az implementációja még változhat, ez majd a felhasználói felületre lesz leginkább hatással
// | | | 
// v v v 
class MonthlyCalendar :public EventStore {
private:
    int selMonth;
public:
    /// @brief Paraméteres konstruktor
    /// @param selMonth kiválasztott hónap (default = 1)
    MonthlyCalendar(int selMonth = 1) :selMonth(selMonth) {}
    void printCalendar();
};

class YearlyCalendar :public EventStore {
private:
    MonthlyCalendar m[12];
    int selYear;
public:
    /// @brief Paraméteres konstruktor
    /// @param selMonth kiválasztott év (default = 1970)
    YearlyCalendar(int selYear = 1970) :selYear(selYear) {}
    void printCalendar();
};

#endif