/**
 * \file interface.h
 *
 * Ez a f�jl tartalmazza az Interface oszt�ly deklar�ci�j�t �s inline f�ggv�nyeit.
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

    std::ostream& os;           ///< ide �rja a kimenet�t
    std::istream& is;           ///< innen olvasssa a bemenet�t

    bool interfacing;           ///< fut-e az interface

    vector<Ugyfel*> ugyfelek;   ///< nyilv�ntartott �gyfelek

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    /// Olvas a bemenetr�l eg�szen sor v�ge jelig.
    string read_input(const string& input_name, const string& input_start_text = "");
    /// Olvas a bemenetr�l biztons�gosan, �s k�r�lv�gva az �g�rt t�pust adja.
    string get_string_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1 );
    int get_number_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1);
    Csomag* get_csomag_input();

    /// Az �gyfelek el�r�se
    bool is_valid_ugyfel_index(int index);
    size_t get_ugyfel_index(int telefonszam);
    Ugyfel* get_ugyfel(int telefonszam);

    /// F�men� �s a hozz� tartoz� v�laszt�s kezel�
    void fomenu();
    void valasztas_kezelo(const string& valasztas);

    /// A men�pontok
    void kilep();               // 0.
    void uj_ugyfel();           // 1.
    void ugyfelek_listazasa();  // 2.
    void ugyfel_torlese();      // 3.
    void ugyfelek_fajlba();     // 4.
    void ugyfelek_fajlbol();    // 5.
    void szamlazas();           // 6.

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
public:
    /// Konstruktor
    /// @param os - ostream, ahova a menu �rja a kimenet�t
    /// @param is - istream, ahonnan olvassa a bemenet�t
    Interface(std::ostream& os, std::istream& is) : os(os), is(is), interfacing(true) {};

    /// Desktuktor
    ~Interface();

    /// F� f�ggv�ny. Meghiv�s�val elindul a kommunik�ci� a felhaszn�l�val.
    /// Kil�p�sig fut.
    void run();

};

#endif // _INTERFACE
