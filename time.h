// time.h időkezelő osztály (deklarációk/inlineok) - 2025.04.05. SAXHSH

class Time {
private:
    int hour;
    int minute;
public:
    Time() :hour(0), minute(0) {}

    Time(int hour, int minute) :hour(hour), minute(minute) {
        if (!isValid) throw std::invalid_argument("Érvénytelen idő!")
    }

    bool isValid();

    /// @brief Getter függvény
    /// @return óra
    int getHour() const { return hour; }

    /// @brief Getter függvény
    /// @return perc
    int getMinute() const { return minute; }
 };
 

    