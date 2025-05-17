// except.h kivételkezelő osztályok - SAXHSH

#ifndef EXCEPT_H
#define EXCEPT_H

#include <stdexcept>

/// @class invalid_date
/// @brief Saját kivételosztály az érvénytelen dátumokra.
/// Az std::invalid_argument osztályból származik le. Más osztály nem származhat le belőle.
struct invalid_date final : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

/// @class invalid_time
/// @brief Saját kivételosztály az érvénytelen időpontokra.
/// Az std::invalid_argument osztályból származik le. Más osztály nem származhat le belőle.
struct invalid_time final : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

/// @class nofind
/// @brief Saját kivételosztály arra, ha a keresés nem talált értéket.
/// Az std::runtime_error osztályból származik le. Más osztály nem származhat le belőle.
struct nofind final : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

/// @class evclash
/// @brief Saját kivételosztály arra, ha két esemény ütközik és ez kivételt jelent.
/// Az std::runtime_error osztályból származik le. Más osztály nem származhat le belőle.
struct evclash final : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

#endif