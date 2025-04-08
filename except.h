#ifndef EXCEPT_H
#define EXCEPT_H

#include <stdexcept>

/// @class invalid_date
/// @brief Saját kivételosztály az érvénytelen dátumokra.
/// Az std::invalid_argument osztályból származik le. Más osztály nem származhat le belőle.
struct invalid_date final : public std::invalid_argument {
    /// @brief Paraméteres konstruktor
    /// @param msg Hibaüzenet
    explicit invalid_date(const char* msg) : std::invalid_argument(msg) {}
};

/// @class invalid_time
/// @brief Saját kivételosztály az érvénytelen időpontokra.
/// Az std::invalid_argument osztályból származik le. Más osztály nem származhat le belőle.
struct invalid_time final : public std::invalid_argument {
    /// @brief Paraméteres konstruktor
    /// @param msg Hibaüzenet
    explicit invalid_time(const char* msg) : std::invalid_argument(msg) {}
};

#endif