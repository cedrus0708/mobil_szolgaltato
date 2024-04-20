#ifndef _MENU
#define _MENU

#include <iostream>

#include "ugyfel.h"
#include "vector.hpp"

using std::cout;
using std::cin;
using std::endl;

class Menu{
    bool interfacing;

    vector<Ugyfel*> ugyfelek;

public:
    Menu() : interfacing(true) {};

    void fomenu(){ // main_menu
        while(interfacing){
            cout << "0. Kiepes a programbol" << endl
                << "1. Ugyfel felvetele" << endl
                << "2. Ugyfelek listazasa" << endl
                << "3. Ugyfel torlese" << endl
                << "4. Ugyfelek fajlba irasa" << endl
                << "5. Ugyfelek betoltese fajlbol" << endl
                << "6. Szamlazas" << endl;
            string valasztas;
            cin >> valasztas;
            valasztas_kezelo(valasztas);
        }
    }

    void valasztas_kezelo(const string& valasztas){
        if     (valasztas == "0") interfacing = false;   // 0. kilep
        else if(valasztas == "1") uj_ugyfel();           // 1. ugyfel felvetele
        else cout << "ertelmezhetetlen";
    }

    void uj_ugyfel(){}


};

#endif // _MENU
