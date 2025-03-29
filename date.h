// date.h dátumkezelő osztály (deklarációk) - 2025.03.29. SAXHSH

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
    /// @brief Getter függvény
    /// @return év
    int getYear() { return year; }

    /// @brief Getter függvény
    /// @return hónap
    int getMonth() { return month; } 

    /// @brief Getter függvény
    /// @return nap
    int getDay() { return day; }

    /// @brief Két dátum összehasonlítása
    /// @param rhs összehasonlítás jobboldala
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