// event.h eseménykezelő osztály (deklarációk/inlineok) - 2025.03.31. SAXHSH

#ifndef EVENT_H
#define EVENT_H

#include "string.h"
#include "datetime.h"

/// @class Event
/// @brief Eseményekhez dátumot és időt, leírást párosító osztály
class Event {
private:
    Datetime evTime; ///< Esemény ideje
    String evDesc; ///< Esemény leírása
public:
    /// @brief Default konstruktor
    Event() :evTime(), evDesc() {}

    /// @brief Paraméteres konstruktor
    /// @param Dt Dátum és idő objektum
    /// @param desc Leírás sztring objektum
    Event(const Datetime& Dt, const String& desc) :evTime(Dt), evDesc(desc) {}

    /// @brief Értékadó operátor
    /// @param rhs Új érték
    /// @return Megváltozott értékű objektum
    Event& operator=(const Event& rhs) {
        if (this != &rhs) {
            evTime = rhs.evTime;
            evDesc = rhs.evDesc;
        }
        return *this;
    }

    /// @brief Esemény összehasonlítása dátum alapján
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs frisebb dátumú-e mint rhs
    bool operator>(const Event& rhs) {
        return evTime > rhs.evTime;
    }

    /// @brief Esemény összehasonlítása dátum alapján
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs régebbi dátumú-e mint rhs
    bool operator<(const Event& rhs) {
        return evTime < rhs.evTime;
    }

    /// @brief Két esemény megegyezősége
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs és rhs megegyező dátumúak-e
    bool operator==(const Event& rhs) {
        return evTime == rhs.evTime;
    }

};

#endif