// string.cpp dinamikus sztringkezelő osztály (definíciók) - 2025.03.28. SAXHSH
#include "string.h"
#include "memtrace.h"
#include <iostream>
#include <cstddef>
#include <cstring>

// Paraméter nélküli konstruktor inline

// Paraméteres konstruktor (1)
String::String(char const *str) :len(strlen(str)), pData(new char[len+1]) {
    strcpy(pData, str);
}

// Paraméteres konstruktor (2) inline

// Másoló konstruktor
String::String(const String& rhs) :len(rhs.len), pData(new char[len+1]) {
    strcpy(pData, rhs.pData);
}

// Destruktor inline

// Getter fv.-ek inline

// Értékadó operátor
String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        delete[] pData;
        len = rhs.len;
        pData = new char[len+1];
        strcpy(pData, rhs.pData);
    }
    return *this;
}

// Hozzáfűző operátor (String)
String String::operator+(const String& rhs) const {
    String newStr;
    newStr.len = len+rhs.len;
    newStr.pData = new char[newStr.len+1];
    strcpy(newStr.pData, pData);
    strcat(newStr.pData, rhs.pData);
    return newStr;
}

// Hozzáfűző operátor (karakter)
String String::operator+(char c) const {
    String newStr;
    newStr.len = len+1;
    newStr.pData = new char[newStr.len+1];
    strcpy(newStr.pData, pData);
    strcat(newStr.pData, String(c).pData);
    return newStr;
}

// Értékadó hozzáfűző operátor (string)
String& String::operator+=(const String& rhs) {
    return (*this = *this + rhs);
}

// Értékadó hozzáfűző operátor (karakter)
String& String::operator+=(char c) {
    return (*this = *this + c);
}

// Módosító indexelő operátor
char& String::operator[](int i) {
    if (i < 0 || i >= len) throw std::out_of_range ("Túlindexelted a sztringet!");
    return pData[i];
}

// Nem módosító indexelő operátor
char String::operator[](int i) const {
    if (i < 0 || i >= len) throw std::out_of_range ("Túlindexelted a sztringet!");
    return pData[i];
}

// lhs nagyobb mint rhs
bool String::operator>(const String& rhs) const {
    return (strcmp(pData, rhs.pData) > 0);
}

// lhs kisebb mint rhs
bool String::operator<(const String& rhs) const {
    return (strcmp(pData, rhs.pData) < 0);
}

// lhs megegyezik rhs-el
bool String::operator==(const String& rhs) const {
    return (strcmp(pData, rhs.pData) == 0);
}

// Kiírás
std::ostream& operator<<(std::ostream& os, const String& rhs) {
    os << rhs.c_str();
    return os;
}

// Beolvasás
std::istream& operator>>(std::istream& is, String& rhs) {
    char c;
    String uj;
    while(is.get(c)) uj += c;
    rhs = uj;
    return is;
}
