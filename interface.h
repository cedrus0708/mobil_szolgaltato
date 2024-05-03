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
private:

    std::ostream& os;           ///< ide írja a kimenetét
    std::istream& is;           ///< innen olvasssa a bemenetét

    bool interfacing;           ///< fut-e az interface

    vector<Ugyfel*> ugyfelek;   ///< nyilvántartott ügyfelekű

    // csomagokbol allo heterogen kollekcio???

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


    /// Olvas a bemenetrõl egészen sor vége jelig.
    string read_input(const string& input_name, const string& input_start_text = "");
    /// Olvas a bemenetrõl biztonságosan, és körülvágva az ígért típust adja.
    string get_string_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1 );
    int get_number_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1);
    Csomag* get_csomag_input(); /// A csomagot lefoglalja. A felszabadítás a hívó feladata!

    /// Ügyfelek vektor kiürítése
    void delete_ugyfelek();

    /// Az ügyfelek elérése
    bool is_valid_ugyfel_index(int index);
    size_t get_ugyfel_index(int telefonszam);
    Ugyfel* get_ugyfel(int telefonszam);


    /// Fõmenü és a hozzá tartozó választás kezelő
    void fomenu();
    void valasztas_kezelo(const string& valasztas);

    /// A menüpontok
    void kilep();               // 0.
    void uj_ugyfel();           // 1.
    void ugyfelek_listazasa();  // 2.
    void ugyfel_torlese();      // 3.
    void ugyfelek_fajlba();     // 4.
    void ugyfelek_fajlbol();    // 5.
    void szamlazas();           // 6.
    void sms_teszt_toggle();

    /// Segédfüggvények a menüpontokhoz
    string szamlazas_szamol(std::ifstream& source_file, std::ostream& os);


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

};

#endif // _INTERFACE
