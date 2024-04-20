#ifndef _STRING
#define _STRING

#include <iostream>
#include "memtrace.h"

/**
 * \file string.h
 *
 * Ez a fájl tartalmazza a String osztály deklarációját és inline függvényeit.
 */

/**
 * String osztály.
 * A pData-ban vannak a karakterek (a lezáró nullával együtt),
 * length: hossz. A hosszba nem számít bele a lezáró nulla.
 */


class string {
    size_t length;  ///< hossz lezáró nulla nélkül
    char* pData;    ///< pointer az adatra

    int countDigits(int number); ///< integer konstruktorhoz

public:

    /// Konstruktor egy char karakterbõl
    /// @param c - karakter
    string(char c);

    /// Konstruktor egy nullával lezárt char sorozatból
    /// @param p - pointer egy C sztringre
    ///        null pointer esetén const char* típusu kivételt dob
    string(const char* p = "");

    /// Konstruktor egy számból
    /// @param value - integer típusú szám
    string(int value);

    /// Másoló konstruktor
    /// @param str - String, amibõl létrehozzuk az új String-et
    string(const string& str);


    /// Destruktor
    ~string(){ delete[] pData; };



    /// C-sztringet ad vissza
    /// @return pointer egy '\0'-val lezárt (C) sztringre
    inline const char* c_str() const { return pData; };

    /// Hossz lekérdezése.
    /// @return Sztring hossza
    inline size_t size() const { return length; };



    /// Értékadó operátor.
    /// @param rhs_s - jobboldali String
    /// @return baoldali (módosított) string (referenciája)
    string& operator=(const string& rhs_s);

    /// Két stringet összefûz
    /// @param rhs_s - jobboldali string
    /// @return új string, ami tartalmazza a két stringet egymás után
    string operator+(const string& rhs_s) const ;

    /// Sztringhez karaktert összefûz
    /// @param rhs_c - jobboldali karakter
    /// @return új string, ami tartalmazza a stringet és a karaktert egymás után
    inline string operator+(char rhs_c) const { return *this + string(rhs_c); }

    /// A string egy megadott indexû elemének referenciájával tér vissza.
    /// @param idx - karakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob.
    char& operator[](unsigned int idx);

    /// A string egy megadott indexû elemének referenciájával tér vissza.
    /// @param idx - karakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob.
    const char& operator[](unsigned int idx) const;

    bool operator==(const string& cmp) const;

    inline bool isEmpty() const { return length == 0; };
};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param s0 - string, amit kiírunk
/// @return os
std::ostream& operator<<(std::ostream& os, const string& s0);

/// Beolvas az istream-rõl egy szót egy string-be.
/// @param is - istream típusú objektum
/// @param s0 - string, amibe beolvas
/// @return is
std::istream& operator>>(std::istream& is, string& s0);

/// Karakterhez stringet fûz
/// @param ch - karakter
/// @param str - string
/// @return új string, ami tartalmazza a karaktert és a stringet egymás után
inline string operator+(char ch, const string& str) { return string(ch) + str; }



#endif // _STRING
