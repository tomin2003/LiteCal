// except.h kivételkezelő osztályok - SAXHSH

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

/// @class nofind
/// @brief Saját kivételosztály arra, ha a keresés nem talált értéket.
/// Az std::runtime_error osztályból származik le. Más osztály nem származhat le belőle.
struct nofind final : public std::runtime_error {
    explicit nofind(const char* msg) : std::runtime_error(msg) {}
};

/// @class evclash
/// @brief Saját kivételosztály arra, ha két esemény ütközik és ez kivételt jelent.
/// Az std::runtime_error osztályból származik le. Más osztály nem származhat le belőle.
struct evclash final : public std::runtime_error {
    explicit evclash(const char* msg) : std::runtime_error(msg) {}
};

#endif