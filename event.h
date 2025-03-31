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

    Event& operator=(const Event& rhs) {
        if (this != &rhs) {
            evTime = rhs.evTime;
            evDesc = rhs.evDesc;
        }
        return *this;
    }
};

#endif