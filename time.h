// time.h időkezelő osztály (deklarációk/inlineok) - SAXHSH

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include "except.h"

/// @class Time
/// @brief Időpontokat nyílvántartó osztály
class Time {
private:
    int hour; ///< óra
    int minute; ///< perc
public:
    /// @brief Default konstruktor
    /// Alapértelmezett időpont: 00:00 (éjfél)
    Time() :hour(0), minute(0) {}

    /// @brief Paraméteres konstruktor
    /// Érvényesség ellenőrzéssel
    /// @param hour óra
    /// @param minute perc
    Time(int hour, int minute) :hour(hour), minute(minute) {
        if (!isValid()) throw invalid_time("Érvénytelen idő!");
    }

    /// @brief Megállapítja egy időpontról, hogy érvényes-e.
    /// @return igen/nem
    bool isValid() const;

    /// @brief Getter függvény
    /// @return óra
    int getHour() const { return hour; }

    /// @brief Getter függvény
    /// @return perc
    int getMinute() const { return minute; }

    /*Megjegyzés: a settereknél a konstruktort újrafuttatom, hogy megmaradjon a hibaellenőrzés az új időpontokra.*/

    /// @brief Setter függvény
    /// @param h óra
    void setHour(int h) { *this = Time(h, minute); }

    /// @brief Setter függvény
    /// @param m perc
    void setMinute(int m) { *this = Time(hour, m); }

    /// @brief Két időpont összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs frisebb időpont-e mint rhs
    bool operator>(const Time& rhs) const;

    /// @brief Két időpont összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs régebbi időpont-e mint rhs
    bool operator<(const Time& rhs) const;

    /// @brief Két időpont összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs és rhs megegyező időpont-e
    bool operator==(const Time& rhs) const;

    /// @brief Két időpont összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs frisebb időpont-e mint rhs, vagy megegyeznek
    bool operator>=(const Time& rhs) const;

    /// @brief Két időpont összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs régebbi időpont-e mint rhs, vagy megegyeznek
    bool operator<=(const Time& rhs) const;
 };

/// @brief Egy időpontot kiíró stream operátor
/// @return output stream (ÓÓ:PP)
std::ostream& operator<<(std::ostream& os, const Time& rhs);

/// @brief Egy időpontot beolvasó stream operátor (ÓÓ:PP)
/// @return input stream 
std::istream& operator>>(std::istream& is, Time& rhs);
 
#endif
    