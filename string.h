/**
 * \file string.h
 *
 * Ez a fájl tartalmazza a String osztály deklarációját és inline függvényeit.
 */
#ifndef _STRING
#define _STRING

#include <iostream>

#include "memtrace.h"


/**
 * String osztály.
 * A pData-ban vannak a karakterek (a lezáró nullával együtt),
 * length: hossz. A hosszba nem számít bele a lezáró nulla.
 */


class string {
    size_t length;  ///< hossz lezáró nulla nélkül
    char* pData;    ///< pointer az adatra

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
    inline ~string(){ delete[] pData; };



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

    /// Két stringet összefűz
    /// @param rhs_s - jobboldali string
    /// @return új string, ami tartalmazza a két stringet egymás után
    string operator+(const string& rhs_s) const ;

    /// Sztringhez karaktert összefűz
    /// @param rhs_c - jobboldali karakter
    /// @return új string, ami tartalmazza a stringet és a karaktert egymás után
    inline string operator+(char rhs_c) const { return *this + string(rhs_c); }

    /// A string egy megadott indexű elemének referenciájával tér vissza.
    /// @param idx - karakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob.
    char& operator[](unsigned int idx);

    /// A string egy megadott indexű elemének referenciájával tér vissza.
    /// @param idx - karakter indexe
    /// @return karakter (referencia)
    ///         Indexelési hiba esetén const char* kivételt dob.
    const char& operator[](unsigned int idx) const;

    /// Két string összehasonlítása.
    /// @param cmp - az összehasonlítandó string
    /// @return egyenlőek-e
    bool operator==(const string& cmp) const;

    /// Üres-e a string.
    /// @return üres-e
    inline bool isEmpty() const { return length == 0; };

    /// Tartalmazza-e a string a megadott karaktert.
    /// @param c - a vizsgált karaker
    /// @return tartalmazza-e
    bool includes(char c) const;

    /// Megkeresi az első olyan indexet, amely tartalmazza a paraméterül kapott string valamelyik karaterét.
    /// @param characters - a karaktereket tartalamzó string
    /// @return az első tartalmazott index
    size_t find_first_of(const string& characters) const;

    /// Megkeresi azt az indexet, ahol utoljára tartalmazza a string a paraméterül kapott string valamelyik karakterét.
    /// @param characters - a karaktereket tartalmazó string
    /// @return az utolsó olyan index, amely még tartalmazza a paraméterül kapott string valamelyik karakterét
    size_t find_last_of(const string& characters) const;

    /// Megkeresi azt az indexet, amely először nem tartalmazza a paraméterül kapott string valamelyik karakterét.
    /// @param characters - a karaktereket tartalmazó string
    /// @return az első index ami már nem tartalmazza a paraméterül kapott string valamelyik elemét
    size_t find_first_not_of(const string& characters) const;

    /// Megkeresi azt az utolsó olyan karaktert a stringben, amely utoljára tartalmaz olyan karaktert, amit a paraméterül kapott string nem.
    /// @param characters - a karaktereket tartalmazó string
    /// @return az utolsó olyan index ami még a megadott string egyik karakterét sem tartalmazza
    size_t find_last_not_of(const string& characters) const;

    /// Elhagyja a strnig elejét az index alapján.
    /// @param start - az uj string eleje (ezt már tartalmazza az uj string)
    /// @return az ujjonan létrejövő string
    ///         Indexelési hiba esetén const char* kivételt dob.
    string& erase(size_t start);

    /// Elhagyja a string elejét és a végét az indexek alapján.
    /// @param start - az uj string errol az indexrol indul (tartalmazza az uj)
    /// @param stop - ettől az indextől már nem tartalmaz semmit (ezt már nem tartalmazza az uj)
    /// @return az így létrejött új string: [start, stop)
    ///         Indexelési hiba esetén const char* kivételt dob.
    string& erase(size_t start, size_t stop);

    /// Levága a string eléről és a végéről a white-space-ket.
    /// @return a körülvágott string
    string& trim();


    /// A stringből mindenhonnan eltávolítja a kapott karaktert.
    /// @param c - az eltávolítandó karakter
    /// @return az igy kialakuló string
    string& remove_all(char c);

    /// Eltávolítja a stringből az összes karaktert, amit a paraméterül kapott stringben előfordul.
    /// @param chars - string, amely az eltávolítandó karaktereket tartalmazza
    /// @return az így létrejövő string
    string& remove_all(const string& chars);

};

/// Globális függvények:
/// kiír az ostream-re
/// @param os - ostream típusú objektum
/// @param s0 - string, amit kiírunk
/// @return os
std::ostream& operator<<(std::ostream& os, const string& s);

/// Beolvas az istream-ről egy szót egy string-be.
/// @param is - istream típusú objektum
/// @param s0 - string, amibe beolvas
/// @return is
std::istream& operator>>(std::istream& is, string& s);

/// Karakterhez stringet fűz
/// @param ch - karakter
/// @param str - string
/// @return új string, ami tartalmazza a karaktert és a stringet egymás után
inline string operator+(char ch, const string& str) { return string(ch) + str; }

/// Megszámolja hány számjegyből áll egy szám.
/// @param number - ennek a számjegyeit számolja
/// @return a számjegyek száma (ha negatív, akkor a negatív jelet is bele számolja)
int countDigits(int number);

/// Stringet számmá alakít.
/// @param str - számmá alakítandó string
/// @return számmá alakítva a string (white spaceket kiszedve, egybe)
int stoi(const string& str);


#endif // _STRING
