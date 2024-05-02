#ifndef _MENU
#define _MENU

#include <iostream>
#include <fstream>

#include "ugyfel.h"
#include "vector.hpp"

using std::endl;

class Menu{
    std::ostream& os; ///< ide �rja a kimenet�t
    std::istream& is; ///< innen olvasssa a bemenet�t

    bool interfacing;

    vector<Ugyfel*> ugyfelek;

    // - - - - - - - - - - - -

    string read_input(const string& input_name, const string& input_start_text = "");

    string get_string_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1 );
    int get_number_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1);
    Csomag* get_csomag_input();

    bool is_valid_ugyfel_index(int index);
    size_t get_ugyfel_index(int telefonszam);
    Ugyfel* get_ugyfel(int telefonszam);

    void fomenu();
    void valasztas_kezelo(const string& valasztas);

    void kilep();
    void uj_ugyfel();
    void ugyfel_torlese();
    void ugyfelek_listazasa();
    void ugyfelek_fajlba();
    void ugyfelek_fajlbol();
    void szamlazas();

public:
    /// Konstruktor
    /// @param os - ostream, ahova a menu �rja a kimenet�t
    /// @param is - istream, ahonnan olvassa a bemenet�t
    Menu(std::ostream& os, std::istream& is) : os(os), is(is), interfacing(true) {};

    /// Desktuktor
    ~Menu();

    /// F� f�ggv�ny. Meghiv�s�val elindul a kommunik�ci� a felhaszn�l�val.
    /// Kil�p�sig fut.
    void run();

    /// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /// Az al�bbi f�ggv�nyek lehet�nek priv�tak is, de a tesztelhet�s�g �rdek�ben publikusak


};

#endif // _MENU
