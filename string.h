// string.h dinamikus sztringkezelő osztály - 2025.03.28. SAXHSH
#ifndef STRING_H
#define STRING_H

/// @class String
/// @brief Egy dinamikus sztringkezelő osztály.
/// RAII elven működő, automatikusan memóriafoglalást és felszabadítást megvalósító osztály, felüldefiniált operátorokkal.
class String {
private:    
    char *pData; ///< Karaktertömb eleje pointer
    size_t len; ///< Sztring hossza
public:
    /// @brief Paraméter nélküli konstruktor
    /// Egy üres sztringet reprezentál
    String() : pData(nullptr), len(0) {}
    
    /// @brief Paraméteres konstruktor
    /// @param str C-string ('\0'-val lezárt)
    String(const char* str);

    /// @brief Másoló konstruktor
    /// @param rhs A másolandó String objektum
    String(const String& rhs);

    /// @brief Destruktor
    ~String();

    /// @brief Getter fügvény
    /// @return String objektum hossza
    size_t getLen() { return len; }


};

#endif