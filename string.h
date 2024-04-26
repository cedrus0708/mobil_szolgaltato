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


    bool includes(char c) const {
        for(size_t i = 0; i < length; ++i)
            if(pData[i] == c) return true;
        return false;
    }

    // visszadja azt az első indexet, amely a string elejétől nézve nem tartalmazza a paraméterül kapott string egyik elemét.
    // (-> a visszadott index már nem tartalmazza)
    size_t find_first_not_of(const string& characters) const {
        size_t i = 0;
        while(characters.includes(pData[i]) && i < length ) i++;
        return i;
    }
    size_t find_last_not_of(const string& characters) const {
        size_t i = size() - 1;
        while(characters.includes(pData[i]) && i > 0 ) i--;
        return i;
    }

    string& erase(size_t start){
        return erase(start, size() - 1);
    }

    // const char* tipusu kivelel
    // elhagyja a megadott index alatti és feletti részeit a stringnek. (maguk az indexek maradnak)
    string& erase(size_t start, size_t stop){
        if(start < 0 || start > stop || stop >= size()) throw "kerem szepen..";

        size_t new_length = stop - start + 1;
        char* new_pData = new char[new_length + 1];
        strncpy(new_pData, pData + start, new_length);
        new_pData[new_length] = '\0';
        delete[] pData;
        pData = new_pData;
        length = new_length;
        return *this;
    }

    string& trim(){
        string white_spaces = " \f\n\r\t\v";

        // trim right
        size_t pos = find_last_not_of( white_spaces );
        erase( 0, pos );

        // trim left
        pos = find_first_not_of( white_spaces );
        erase( pos );

        return *this;
    }

    string& remove_all(char c) {
        size_t new_length = 0;
        for (size_t i = 0; i < length; ++i)
            if(pData[i] != c) new_length++;
        char* new_pData = new char[new_length + 1];
        size_t new_pData_index = 0;
        for (size_t i = 0; i < length; ++i)
            if( pData[i] != c ) new_pData[new_pData_index++] = pData[i];
        delete[] pData;
        pData = new_pData;
        length = new_length;
        return *this;
    }

};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param s0 - string, amit kiírunk
/// @return os
std::ostream& operator<<(std::ostream& os, const string& s);

/// Beolvas az istream-rõl egy szót egy string-be.
/// @param is - istream típusú objektum
/// @param s0 - string, amibe beolvas
/// @return is
std::istream& operator>>(std::istream& is, string& s);

/// Karakterhez stringet fûz
/// @param ch - karakter
/// @param str - string
/// @return új string, ami tartalmazza a karaktert és a stringet egymás után
inline string operator+(char ch, const string& str) { return string(ch) + str; }

int stoi(const string& str);


#endif // _STRING
