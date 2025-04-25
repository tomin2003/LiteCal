// string.h dinamikus sztringkezelő osztály (deklarációk/inlineok) - 2025.03.28. SAXHSH
#ifndef STRING_H
#define STRING_H

#include <cstddef>
#include <iostream>

/// @class String
/// @brief Egy dinamikus sztringkezelő osztály
/// RAII elven működő, automatikusan memóriafoglalást és felszabadítást megvalósító osztály, felüldefiniált operátorokkal.
class String {
private:    
    size_t len; ///< Sztring hossza
    char *pData; ///< Karaktertömb eleje pointer
public:
    /// @brief Paraméter nélküli konstruktor
    /// Egy üres sztringet reprezentál
    String() : len(0), pData(new char[1]{'\0'}) {}

    /// @brief Paraméteres konstruktor
    /// Karakterből String objektumot készít.
    /// @param c Karakter
    String(char c) :len(1), pData(new char[2]{c, '\0'}) {}
    
    /// @brief Paraméteres konstruktor
    /// C-stringből String objektumot készít.
    /// @param str C-string ('\0'-val lezárt)
    String(const char* str);

    /// @brief Másoló konstruktor
    /// @param rhs A másolandó String objektum
    String(const String& rhs);

    /// @brief Destruktor
    ~String() { delete[] pData; }

    /// @brief Getter fügvény
    /// @return String objektum hossza
    size_t getLen() const { return len; }

    /// @brief Getter függvény
    /// @return C-sztring (read only)
    char const* c_str() const { return pData; }

    /// @brief Értékadó operátor
    /// Fontos értékadó operátort definiálni a helyes memóriakezelés érdekében.
    /// @param rhs Értékként adott String objektum
    /// @return *this pointer
    String& operator=(const String& rhs);

    /// @brief Sztring hozzáfűzés
    /// Az "strcat" C függvényt alkalmazza.
    /// @param rhs Jobbról hozzáfűzött String
    /// @return Új String objektum
    String operator+(const String& rhs) const;

    /// @brief Sztring hozzáfűzés
    /// Az "strcat" C függvényt alkalmazza.
    /// @param rhs Jobbról hozzáfűzött karakter
    /// @return Új String objektum
    String operator+(char c) const;

    /// @brief Értékadó hozzáfűzés
    /// @param rhs A hozzáfűzendő String
    /// @return Hozzáfűzött String
    String& operator+=(const String& rhs);

    /// @brief Értékadó hozzáfűzés
    /// @param rhs A hozzáfűzendő karakter
    /// @return Hozzáfűzött String
    String& operator+=(char c);
    
    /// @brief Indexelő operátor
    /// Módosíthatja a hívó objektumot. Végez indexellenőrzést, kivétellel tér vissza érvénytelen indexelés esetén.
    /// @param i index
    /// @return indexelt elem referenciája
    char& operator[](int i);
    
    /// @brief Indexelő operátor
    /// NEM módosíthatja a hívó objektumot. Végez indexellenőrzést, kivétellel tér vissza érvénytelen indexelés esetén.
    /// @param i index
    /// @return indexelt elem értéke
    char operator[](int i) const;

    /// @brief ABC sorrend szerinti összehasonlítása két sztringnek
    /// @param rhs A hívóval összehasonlítandó String
    /// @return lhs előrébb van-e az ABC-ben, mint rhs
    bool operator>(const String& rhs) const;

    /// @brief ABC sorrend szerinti összehasonlítása két sztringnek
    /// @param rhs A hívóval összehasonlítandó String
    /// @return lhs hátrébb van-e az ABC-ben, mint rhs
    bool operator<(const String& rhs) const;

    /// @brief Két sztring megegyező-e
    /// @param rhs A hívóval összehasonlítandó String
    /// @return lhs ugyanaz-e, mint rhs
    bool operator==(const String& rhs) const;
};

/// @brief Streamre történő kiírása egy Stringnek
/// @return Output stream
std::ostream& operator<<(std::ostream& os, const String& rhs);

/// @brief Streamről történő beolvasás egy Stringbe.
/// @return Input stream
std::istream& operator>>(std::istream& is, String& rhs);

#endif