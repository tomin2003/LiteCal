// date.h dátum és időkezelő osztály (deklarációk/inlineok) - 2025.03.31. SAXHSH
#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>

/// @class Datetime
/// @brief Dátumokat és időpontokat nyílvántartó osztály
class Datetime {
private:
    int year; ///< év
    int month; ///< hónap
    int day; ///< nap
    int hour; ///< óra
    int minute; ////< perc
    static const int monthDays[12]; ///< adott hónapban a napok száma
    static const char* weekDays[7]; ///< a hét napjai
public:
    /// @brief Default konstruktor
    /// Alapértelmezett dátum 1970.01.01. 00:00 (Unix time)
    Datetime() :year(1970), month(1), day(1), hour(0), minute(0)  {}

    /// @brief Paraméteres konstruktor
    /// @param year év
    /// @param month hónap
    /// @param day nap
    /// @param hour óra
    /// @param minute perc
    Datetime(int year, int month, int day, int hour, int minute) :year(year), month(month), day(day), hour(hour), minute(minute) {}

    /// @brief Getter függvény
    /// @return év
    int getYear() const { return year; }

    /// @brief Getter függvény
    /// @return hónap
    int getMonth() const { return month; } 

    /// @brief Getter függvény
    /// @return nap
    int getDay() const { return day; }

    /// @brief Getter függvény
    /// @return óra
    int getHour() const { return hour; }

    /// @brief Getter függvény
    /// @return perc
    int getMinute() const { return minute; }

    /// @brief Megállapítja egy évről, hogy az szökőév-e
    /// @return igen/nem
    bool isLeapYear() const;

    /// @brief Megállapítja egy paraméterként kapott évről, hogy az szökőév-e
    /// Ez csak a kompatibilitás megőrzése miatt tagfüggvény!
    /// @return igen/nem
    bool isLeapYear(int) const;
    
    /// @brief Megállapítja egy dátumról, hogy érvényes-e.
    /// @return igen/nem
    bool isValid() const;
    
    /// @brief Egy dátum reprezentációja napokban
    /// @return 1970.01.01. (unix epoch) óta eltelt napok száma
    int dateInDays() const;

    /// @brief Megállapítja, hogy egy dátum milyen napra esik.
    /// Ehhez a "Zeller's congruence" nevű algoritmust használtam. 
    /// Forrás: https://www.geeksforgeeks.org/zellers-congruence-find-day-date/
    /// @return A hét egy adott napja
    const char* getWeekDay() const;

    /// @brief Két dátum és idő összehasonlítása
    /// @param rhs összehasonlítás jobboldalayy
    /// @return lhs frisebb dátum és idő-e mint rhs
    bool operator>(const Datetime& rhs) const;

    /// @brief Két dátum és idő összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs régebbi dátum és idő-e mint rhs
    bool operator<(const Datetime& rhs) const;

    /// @brief Két dátum és idő összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs és rhs megegyező dátum és idő-e
    bool operator==(const Datetime& rhs) const;

    /// @brief Két dátum között eltelt napok száma
    /// @param rhs másik dátum
    /// @return eltelt napok száma
    int operator-(const Datetime& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Datetime& rhs);

#endif