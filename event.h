// event.h eseménykezelő osztály (deklarációk/inlineok) - 2025.03.31. SAXHSH

#ifndef EVENT_H
#define EVENT_H

#include "string.h"
#include "date.h"
#include "time.h"

/// @class Event
/// @brief Eseményekhez dátumot, időt, és leírást párosító osztály
class Event {
private:
    Date evDate; ///< Esemény dátuma
    Time evTime; ///< Esemény ideje
    String evDesc; ///< Esemény leírása
public:
    /// @brief Default konstruktor
    Event() :evDate(), evTime(), evDesc() {}

    /// @brief Paraméteres konstruktor
    /// @param  Dátum és idő objektum
    /// @param desc Leírás sztring objektum
    Event(const Date& evDate, const Time& evTime, const String& evDesc) :evDate(evDate), evTime(evTime), evDesc(evDesc) {}

    Datetime getEvDate() const { return evDate; }

    Datetime getEvTime() const { return evTime; }

    String getEvDesc() const { return evDesc; }

    /// @brief Értékadó operátor
    /// @param rhs Új érték
    /// @return Megváltozott értékű objektum
    Event& operator=(const Event& rhs);

    /// @brief Esemény összehasonlítása dátum alapján
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs frisebb dátumú-e mint rhs
    bool operator>(const Event& rhs);

    /// @brief Esemény összehasonlítása dátum alapján
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs régebbi dátumú-e mint rhs
    bool operator<(const Event& rhs);

    /// @brief Két esemény megegyezősége
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs és rhs megegyező dátumúak-e
    bool operator==(const Event& rhs);
};

std::ostream& operator<<(std::ostream& os, const Event& rhs);

#endif