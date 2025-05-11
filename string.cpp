// string.cpp dinamikus sztringkezelő osztály (definíciók) - SAXHSH
#include "string.h"
#include "memtrace.h"
#include <iostream>
#include <cstddef>
#include <cstring>

/* Konstruktorok */

// default és karakter paraméteres a headerben

String::String(char const *str) :len(strlen(str)), pData(new char[len+1]) {
    strcpy(pData, str);
}

String::String(const String& rhs) :len(rhs.len), pData(new char[len+1]) {
    strcpy(pData, rhs.pData);
}

// Destruktor és getterek a headerben

/* Felüldefiniált operátorok */

String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        delete[] pData;
        len = rhs.len;
        pData = new char[len+1];
        strcpy(pData, rhs.pData);
    }
    return *this;
}

String String::operator+(const String& rhs) const {
    String newStr;
    newStr.len = len + rhs.len;
    delete[] newStr.pData;
    newStr.pData = new char[newStr.len + 1];
    strcpy(newStr.pData, pData);
    strcat(newStr.pData, rhs.pData);
    return newStr;
}

String String::operator+(char c) const {
    String newStr;
    newStr.len = len + 1;
    delete[] newStr.pData;
    newStr.pData = new char[newStr.len + 1];
    strcpy(newStr.pData, pData);
    newStr.pData[len] = c;
    newStr.pData[len + 1] = '\0';
    return newStr;
}

String& String::operator+=(const String& rhs) {
    return (*this = *this + rhs);
}

String& String::operator+=(char c) {
    return (*this = *this + c);
}

char& String::operator[](int i) {
    if (i < 0 || i >= static_cast<int>(len)) throw std::out_of_range ("Túlindexelted a sztringet!");
    return pData[i];
}

char String::operator[](int i) const {
    if (i < 0 || i >= static_cast<int>(len)) throw std::out_of_range ("Túlindexelted a sztringet!");
    return pData[i];
}

/* Logikai operátorok */

bool String::operator>(const String& rhs) const {
    return (strcmp(pData, rhs.pData) > 0);
}

bool String::operator<(const String& rhs) const {
    return (strcmp(pData, rhs.pData) < 0);
}

bool String::operator==(const String& rhs) const {
    return (strcmp(pData, rhs.pData) == 0);
}

/* Stream operátorok */

std::ostream& operator<<(std::ostream& os, const String& rhs) {
    os << rhs.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, String& rhs) {
    char c; // szimpla karakter buffer
    while(is.get(c)) rhs += c;
    return is;
}
