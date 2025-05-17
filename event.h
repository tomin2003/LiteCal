// event.h eseménykezelő osztály (deklarációk/inlineok) - SAXHSH

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
    /// @param evDate Dátum objektum
    /// @param evTime Idő objektum
    /// @param desc Leírás sztring objektum
    Event(const Date& evDate, const Time& evTime, const String& evDesc) :evDate(evDate), evTime(evTime), evDesc(evDesc) {}

    /// @brief Paraméteres konstruktor
    /// @param y Év
    /// @param mo Hónap
    /// @param d Nap
    /// @param h Óra
    /// @param mi Perc
    /// @param desc Leírás sztring objektum
    Event(int y, int mo, int d, int h, int mi, const String& evDesc) :evDate(y, mo, d), evTime(h, mi), evDesc(evDesc) {}

    /// @brief Getter függvény
    /// @return Dátum objektum
    Date getEvDate() const { return evDate; }

    /// @brief Getter függvény
    /// @return Idő objektum
    Time getEvTime() const { return evTime; }

    /// @brief Getter függvény
    /// @return String objektum
    String getEvDesc() const { return evDesc; }

    /// @brief Setter függvény
    /// @param date dátum
    void setEvDate(Date date) { evDate = date; }

    /// @brief Setter függvény
    /// @param time időpont
    void setEvTime(Time time) { evTime = time; }

    /// @brief Setter függvény
    /// @param desc leírás
    void setEvDesc(String desc) { evDesc = desc; }

    /// @brief Értékadó operátor
    /// @param rhs Új érték
    /// @return Megváltozott értékű objektum
    Event& operator=(const Event& rhs);

    /// @brief Esemény összehasonlítása dátum alapján
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs frisebb dátumú-e mint rhs
    bool operator>(const Event& rhs) const;

    /// @brief Esemény összehasonlítása dátum alapján
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs régebbi dátumú-e mint rhs
    bool operator<(const Event& rhs) const;

    /// @brief Két esemény megegyezősége
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs és rhs megegyező dátumúak-e
    bool operator==(const Event& rhs) const;
};

/// @brief Egy eseményt kiíró stream operátor.
/// @return Output stream (ÉÉÉÉ. HH. NN. ÓÓ:PP - LEÍRÁS)
std::ostream& operator<<(std::ostream& os, const Event& rhs);

/// @brief Egy eseményt beolvasó stream operátor. (ÉÉÉÉ. HH. NN. ÓÓ:PP - LEÍRÁS)
/// @return Input stream 
std::istream& operator>>(std::istream& is, Event& rhs);

#endif