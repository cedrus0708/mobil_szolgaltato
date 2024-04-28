#ifndef _MENU
#define _MENU

#include <iostream>

#include "ugyfel.h"
#include "vector.hpp"

using std::endl;

class Menu{
    std::ostream& os;
    std::istream& is;

    bool interfacing;

    vector<Ugyfel*> ugyfelek;
// --------------------

    //template<typename T>
    string get_input(string input_name, string input_start_text = ""){ // validate input... ,validation type...
        os << '\t' << input_name << ": " << input_start_text;
        string input;
        is >> std::skipws >> input;
        //std::cout << "   " <<  input;
        //is >> input;
        return input;
    };

    void kilep(){
        os << "Kilepes a programbol..." << endl;
        interfacing = false;
    }

    Ugyfel* get_ugyfel(int telefonszam){
        int ugyfelek_szama = ugyfelek.size();
        for(int i = 0; i < ugyfelek_szama; ++i){
    }

    void uj_ugyfel(){
        os << "Uj ugyfel letrehozasa." << endl << "Ugyfel adatai:" << endl;
        // telefonszam
        int telefonszam = stoi(get_input("telefonszam", "+36"));
        int tel_length = countDigits(telefonszam);
        while(tel_length > 9 || tel_length < 1) {
                os << "\t\tNem nemgelelo bemenet. (elvart bemenet hossza: 1-9)" << endl;
                telefonszam = stoi(get_input("telefonszam", "+36"));  tel_length = countDigits(telefonszam);}
        // név
        string nev = get_input("nev").trim();
        while(nev.size() < 1) {
            os << "\t\tNem megfelelo bemenet. (elvart hossz legalabb 1)" << endl;
            nev = get_input("nev").trim();
        }
        // cím
        string cim = get_input("cim").trim();
        while(cim.size() < 1) {
            os << "\t\tNem megfelelo bemenet. (elvart hossz legalabb 1)" << endl;
            cim = get_input("cim").trim();
        }

        // check if ugyfel already exists
        // get_ugyfel(telefonszam)
        Ugyfel* ugyfel = get_ugyfel(telefonszam);
        if(ugyfel != nullptr) {
            os << "Ugyfel letrehozasa SIKERTELEN!\n\tMar letetik ugyfel a megadott telefonszammal." << endl;
            return;
        }

        //ugyfelek.push_back(new Ugyfel( static_cast<int>(telefonszam), nev, cim, new AlapCsomag("alap") ));
        ugyfelek.push_back(new Ugyfel( telefonszam, nev, cim, new AlapCsomag("alap") ));
        os << "Ugyfel sikeresen letrehozva." << endl;
    }

    void ugyfelek_listazasa(){
        int ugyfelek_szama = ugyfelek.size();
        if(ugyfelek.isEmpty()) { os << "Nincsenek ugyfelek a rendszerben!" << endl; return; }
        os << "Ugyfelek a rendszerben:" << endl;
        for(int i = 0; i < ugyfelek_szama; ++i){
            //os << i+1 << ". " << (*ugyfelek[i]) << endl;

            os << i+1 << ".\ttelefonszam: +36" << ugyfelek[i]->getTel() << endl
                << "\tnev: " << ugyfelek[i]->getNev() << endl
                << "\tcim: " << ugyfelek[i]->getCim() << endl;
        }
    }

public:
    Menu(std::ostream& os, std::istream& is) : os(os), is(is), interfacing(true) {};

    void fomenu(){ // main_menu
        while(interfacing){
            os << endl << "Valassz az alabbi lehetosegek kozul" << endl;
            os << "0. Kiepes a programbol" << endl
                << "1. Ugyfel felvetele" << endl
                << "2. Ugyfelek listazasa" << endl
                << "3. Ugyfel torlese" << endl
                << "4. Ugyfelek fajlba irasa" << endl
                << "5. Ugyfelek betoltese fajlbol" << endl
                << "6. Szamlazas" << endl;

            string valasztas = get_input("Valasztas");

            valasztas_kezelo(valasztas);
        }
    }

    void valasztas_kezelo(const string& valasztas){
        if     (valasztas == "0") kilep();   // 0. kilep
        else if(valasztas == "1") uj_ugyfel();           // 1. ugyfel felvetele
        else if(valasztas == "2") ugyfelek_listazasa();
        else os << "ertelmezhetetlen";
    }




};

#endif // _MENU
