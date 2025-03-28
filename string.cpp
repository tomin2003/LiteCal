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




