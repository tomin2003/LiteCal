// date.h dátumkezelő osztály (deklarációk/inlineok) - SAXHSH
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include "except.h"

/// @class Date
/// @brief Dátumokat nyílvántartó osztály
class Date {
private:
    int year; ///< év
    int month; ///< hónap
    int day; ///< nap
    static const char* weekDays[7]; ///< a hét napjai
public:
    /// @brief Default konstruktor
    /// Alapértelmezett dátum 1970.01.01. (Unix time)
    Date() :year(1970), month(1), day(1) {}

    /// @brief Paraméteres konstruktor
    /// Érvényesség ellenőrzéssel
    /// @param year év
    /// @param month hónap
    /// @param day nap
    Date(int year, int month, int day) :year(year), month(month), day(day) {
        if (!isValid()) throw invalid_date("Érvénytelen dátum!");
    }

    /// @brief Getter függvény
    /// @return év
    int getYear() const { return year; }

    /// @brief Getter függvény
    /// @return hónap
    int getMonth() const { return month; } 

    /// @brief Getter függvény
    /// @return nap
    int getDay() const { return day; }

    /*Megjegyzés: a settereknél a konstruktort újrafuttatom, hogy megmaradjon a hibaellenőrzés az új dátumokra.*/

    /// @brief Setter függvény
    /// @param év
    void setYear(int y) { *this = Date(y, month, day); }

    /// @brief Setter függvény
    /// @param hónap
    void setMonth(int m) { *this = Date(year, m, day); }

    /// @brief Setter függvény
    /// @param nap
    void setDay(int d) { *this = Date(year, month, d); }

    /// @brief Megállapítja egy dátumról, hogy érvényes-e.
    /// @return igen/nem
    bool isValid() const;
    
    /// @brief Egy dátum reprezentációja napokban
    /// @return 1970.01.01. (unix epoch) óta eltelt napok száma
    int dateInDays() const;

    /// @brief Megállapítja egy évről, hogy az szökőév-e
    /// @return igen/nem
    bool isLeapYear() const;

    /// @brief Megállapítja egy évről, hogy az szökőév-e
    /// @param y év
    /// @return igen/nem
    bool isLeapYear(int y) const;

    /// @brief Megállapítja, hány napos egy hónap.
    /// @return napok száma
    int daysInMonth(int m) const;

    /// @brief Megállapítja, hogy egy dátum milyen napra esik.
    /// Ehhez a "Zeller's congruence" nevű algoritmust használtam. 
    /// Forrás: https://www.geeksforgeeks.org/zellers-congruence-find-day-date/
    /// @return A hét egy adott napja
    const char* getWeekDay() const;

    /// @brief Megállapítja, hogy egy dátum milyen napra esik.
    /// Ehhez a "Zeller's congruence" nevű algoritmust használtam. 
    /// Forrás: https://www.geeksforgeeks.org/zellers-congruence-find-day-date/
    /// @return A hét egy adott napjának indexe (Hétfő = 0, Vasárnap = 6)
    size_t getWeekDayIdx() const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs frisebb dátum-e mint rhs
    bool operator>(const Date& rhs) const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs régebbi dátum-e mint rhs
    bool operator<(const Date& rhs) const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs és rhs megegyező dátum-e
    bool operator==(const Date& rhs) const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs frisebb dátum-e mint rhs, vagy megegyeznek
    bool operator>=(const Date& rhs) const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs régebbi dátum-e mint rhs, vagy megegyeznek
    bool operator<=(const Date& rhs) const;

    /// @brief Milyen dátum lesz adott nap elteltével
    /// @param day + hány nap
    /// @return Az új dátum
    Date operator+(int rhs) const;

    /// @brief Két dátum között eltelt napok száma
    /// @param rhs másik dátum
    /// @return eltelt napok száma
    int operator-(const Date& rhs) const;
};

/// @brief Egy dátumot kiíró stream operátor
/// @return output stream (ÉÉÉÉ. HH. NN.)
std::ostream& operator<<(std::ostream& os, const Date& rhs);

/// @brief Egy dátumot beolvasó stream operátor (ÉÉÉÉ. HH. NN.)
/// @return input stream 
std::istream& operator>>(std::istream& is, Date& rhs);

#endif