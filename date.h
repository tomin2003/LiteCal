// date.h dátumkezelő osztály (deklarációk/inlineok) - 2025.03.29. SAXHSH
#ifndef DATE_H
#define DATE_H

/// @class Date
/// @brief Dátumokat nyílvántartó osztály
class Date {
private:
    int year; ///< év
    int month; ///< hónap
    int day; ///< nap
    static const int monthDays[12]; ///< adott hónapban a napok száma
    static const char* weekDays[7]; ///< a hét napjai
public:
    /// @brief Default konstruktor
    /// Alapértelmezett dátum 1970.01.01. (Unix time)
    Date() :year(1970), month(1), day(1)  {}

    /// @brief Paraméteres konstruktor
    /// @param year év
    /// @param month hónap
    /// @param day nap
    Date(int year = 1970, int month = 1, int day = 1) :year(year), month(month), day(day) {}

    /// @brief Getter függvény
    /// @return év
    int getYear() const { return year; }

    /// @brief Getter függvény
    /// @return hónap
    int getMonth() const { return month; } 

    /// @brief Getter függvény
    /// @return nap
    int getDay() const { return day; }

    /// @brief Megállapítja egy évről, hogy az szökőév-e
    /// @return igen/nem
    bool isLeapYear() const;

    /// @brief Megállapítja egy dátumról, hogy érvényes-e.
    /// @return igen/nem
    bool isValid() const;

    /// @brief Megállapítja, hogy egy dátum milyen napra esik.
    /// Ehhez a "Zeller's congruence" nevű algoritmust használtam. 
    /// Forrás: https://www.geeksforgeeks.org/zellers-congruence-find-day-date/
    /// @return A hét egy adott napja
    const char* getWeekDay() const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldalayy
    /// @return lhs frisebb dátum mint rhs
    bool operator>(const Date& rhs) const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs régebbi dátum mint rhs
    bool operator<(const Date& rhs) const;

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
    /// @return lhs és rhs megegyező dátumok
    bool operator==(const Date& rhs) const;
};

#endif