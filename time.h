// time.h időkezelő osztály (deklarációk/inlineok) - 2025.03.30. SAXHSH

#ifndef TIME_H
#define TIME_H

/// class Time
/// @brief Idő nyílvántartására szolgáló osztály.
/// Az eseményhez tartozik.
class Time {
private:
    int hour; ///< óra
    int minute; ///< perc
public:
    /// @brief Default konstruktor
    /// Éjfélt állít be alapértelmezetten.
    Time() :hour(0), minute(0) {}

    /// @brief Paraméteres konstruktor
    /// @param hour óra (def. = 0)
    /// @param minute perc (def. = 0)
    Time(int hour = 0, int minute = 0) :hour(hour), minute(minute) {}

    /// @brief Getter függvény
    /// @return óra
    int getHour() const { return hour; }

    /// @brief Getter függvény
    /// @return perc
    int getMinute() const { return minute; }

    /// @brief Megállapítja egy időről, hogy érvényes-e.
    /// @return igen/nem
    bool isValid() const;
    
    /// @brief Összehasonlít két dátumot.
    /// @param rhs Összehasonlítás jobb oldala
    /// @return lhs frisebb mint rhs
    bool operator>(const Time& rhs) const;
};

#endif