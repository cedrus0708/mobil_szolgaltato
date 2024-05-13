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
    void szamlazas_szamol(std::ifstream& source_file, std::ostream& destination_stream) const;


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
    /// @param input_name - az input mező neve, ami után kettőspont kerül
    /// @param input_start_text - az input el van kezdve ezzel a szöveggel (az eredményben nincs benne)
    /// @return a beolvasott string -> (enterig olvas)
    string read_input(const string& input_name, const string& input_start_text = "") const;
    /// Olvas a bemenetrõl biztonságosan, és körülvágva az ígért típust adja.
    /// @param input_name - az input mező neve, ami után kettőspont kerül
    /// @param input_start_text - az input el van kezdve ezzel a szöveggel (az eredményben nincs benne)
    /// @param min_length - az elfogadott minimális hossz
    /// @param max_length - az elfogadott maxumális hossz
    /// @return a feltételeknek megfelelő és körülvágott (string::trim) string
    string get_string_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = std::numeric_limits<size_t>::max() ) const;
    /// Olvas a bemenetrõl biztonságosan, és körülvágva az ígért típust adja.
    /// @param input_name - az input mező neve, ami után kettőspont kerül
    /// @param input_start_text - az input el van kezdve ezzel a szöveggel (az eredményben nincs benne)
    /// @param min_length - az elfogadott minimális hossz
    /// @param max_length - az elfogadott maxumális hossz
    /// @param min_value - minimális érték, amit be még lehet írni
    /// @param max_value - maximális érték, amit be még lehet írni
    /// @return a feltételeknek megfelelően beolvasott szám
    int get_number_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = std::numeric_limits<size_t>::max(),  const int min_value = std::numeric_limits<int>::min(), const int max_value = std::numeric_limits<int>::max() ) const;
    /// Olvas a bemenetrõl biztonságosan, és körülvágva az ígért típust adja.
    /// @return a lefoglalt csomagra mutató pointer
    ///     A csomagot lefoglalja. A felszabadítás a hívó feladata!
    Csomag* get_csomag_input() const;


    // Az ügyfelek elérése és kezelése
    /// Eldönti, hogy van-e ügyfél a vektorban a megadott indexel
    /// @param index - ez eldöntendő index
    /// @return tartalmaz-e a vektor ügyfelet a megadott indexel
    bool is_valid_ugyfel_index(const int index) const;
    /// Visszaadja az ügyfélre mutató indexet a vectorban.
    /// @param telefonszam - az ügyfél telefonszáma
    /// @return a vectoron belüli index, amely a keresett ügyfélre mutat - találat hiányában a vector méretét adja (ami egy nem valós index)
    size_t get_ugyfel_index(const int telefonszam) const;
    /// Az ügyfelek telefonszám szerinti elérése
    /// @param telefonszam - a keresett ügyfél telefonszáma (egyedi azonosítója)
    /// @return a talált ügyfélre mutató konstans pointer - találat hiányában nullpointert ad
    const Ugyfel* const get_ugyfel(const int telefonszam) const;
    /// Kitörli az ügyfelet.
    /// @param telefonszam - egyben egyedi azonosítója az ügyfélnek
    /// @param nev - az ügyfél neve
    /// @param cim - az ügyfél címe
    ///     Ha az ügyfél nem található, akkor std::invalid_argument típusú hibát dob.
    void delete_ugyfel(const int telefonszam, const string& nev, const string& cim);

    /// Ügyfelek vektor kiürítése
    void delete_ugyfelek();


};

#endif // _INTERFACE
