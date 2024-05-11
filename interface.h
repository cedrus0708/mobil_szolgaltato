/**
 * \file interface.h
 *
 * Ez a fájl tartalmazza az Interface osztály deklarációját és inline függvényeit.
 */
#ifndef _INTERFACE
#define _INTERFACE

#include <iostream>
#include <fstream>

#include "ugyfel.h"
#include "vector.hpp"

#include "memtrace.h"

using std::endl;

class Interface{
protected:

    std::ostream& os;           ///< ide írja a kimenetét
    std::istream& is;           ///< innen olvasssa a bemenetét

    bool interfacing;           ///< fut-e az interface

    vector<Ugyfel*> ugyfelek;   ///< nyilvántartott ügyfelek

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


    /// Fõmenü és a hozzá tartozó választás kezelő
    void fomenu() const;
    void valasztas_kezelo(const string& valasztas);

    /// A menüpontok
    void kilep();                       // 0.
    void uj_ugyfel();                   // 1.
    void ugyfelek_listazasa() const;    // 2.
    void ugyfel_torlese();              // 3.
    void ugyfelek_fajlba() const;       // 4.
    void ugyfelek_fajlbol();            // 5.
    void szamlazas() const;             // 6.
    void sms_teszt_toggle() const;      // 7.

    /// Segédfüggvények a menüpontokhoz(1db)
    string szamlazas_szamol(std::ifstream& source_file, std::ostream& os) const;


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
public:
    /// Konstruktor
    /// @param os - ostream, ahova a menu írja a kimenetét
    /// @param is - istream, ahonnan olvassa a bemenetét
    Interface(std::ostream& os, std::istream& is) : os(os), is(is), interfacing(true) {};

    /// Desktuktor
    ~Interface();

    /// Fõ függvény. Meghivásával elindul a kommunikáció a felhasználóval.
    /// Kilépésig fut.
    void run();


    /// Le lehet kérni, hogy fut-e
    /// @return fut-e jelenleg az interface
    inline bool is_interfaceing() const { return interfacing; };


    /// Olvas a bemenetrõl egészen sor vége jelig.
    string read_input(const string& input_name, const string& input_start_text = "") const;
    /// Olvas a bemenetrõl biztonságosan, és körülvágva az ígért típust adja.
    string get_string_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1 ) const;
    int get_number_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = std::numeric_limits<size_t>::infinity(),  const int min_value = std::numeric_limits<int>::min(), const int max_value = std::numeric_limits<int>::max() ) const;
    Csomag* get_csomag_input() const; /// A csomagot lefoglalja. A felszabadítás a hívó feladata!

    /// Ügyfelek vektor kiürítése
    void delete_ugyfelek();

    /// Az ügyfelek elérése
    bool is_valid_ugyfel_index(const int index) const;
    size_t get_ugyfel_index(const int telefonszam) const;
    Ugyfel* get_ugyfel(const int telefonszam) const;


};

#endif // _INTERFACE
