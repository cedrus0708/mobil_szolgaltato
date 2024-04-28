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

    string read_input(const string& input_name, const string& input_start_text = ""){
        os << '\t' << input_name << ": " << input_start_text;
        string input;
        is >> std::skipws >> input;
        return input;
    };

    string get_string_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1 ){
        string text = read_input(input_name, input_start_text).trim();
        while(text.size() < min_length || text.size() > max_length ) {
            os << "\t\tNem megfelelo bemenet. (elvart hossz legalabb " << min_length << ')' << endl;
            text = read_input(input_name, input_start_text).trim();
        }
        return text;
    }

    Csomag* get_csomag_input(){
        Csomag* csomag;
        //string csomag_name = read_input("csomag");

        /*os << "\tcsomag: ";
        is >> csomag;
        while(csomag == nullptr){
            os << "\tcsomag: ";
            is >> csomag;
        }*/

        int csomag_szam = 0;
        while( csomag_szam > 3 || csomag_szam < 1){
            os << "\tcsomag:" << endl
                << "\t\t1. AlapCsomag" << endl
                << "\t\t2. MobiNet" << endl
                << "\t\t3. SMSMax" << endl;
            csomag_szam = get_number_input("\t\tcsomag szama", "", 1, 1);

            if(csomag_szam == 1) csomag = new AlapCsomag("AlapCsomag");
            else if(csomag_szam == 2) csomag = new MobiNet("MobiNet");
            else if(csomag_szam == 3) csomag = new SMSMax("SMSMax");
        }

        return csomag;
    }

    int get_number_input(const string& input_name, const string& input_start_text = "", const size_t min_length = 1, const size_t max_length = -1){
        int number = stoi(read_input(input_name, input_start_text));
        size_t number_length = countDigits(number);
        while(number_length > max_length || number_length < min_length) {
                os << "\t\tNem megfelelo bemenet. (elvart bemenet hossza: " << min_length << '-' << max_length << ")(szamok)" << endl;
                number = stoi(read_input(input_name, input_start_text));  number_length = countDigits(number);
        }
        return number;
    }

    void kilep(){
        os << "Kilepes a programbol..." << endl;
        interfacing = false;
    }

    size_t get_ugyfel_index(int telefonszam){
        size_t ugyfelek_szama = ugyfelek.size();
        for(size_t i = 0; i < ugyfelek_szama; ++i){
            if(ugyfelek[i]->getTel() == telefonszam)
                return i;
        }
        return ugyfelek_szama;
    }

    bool is_valid_ugyfel_index(int index){
        return (index >= 0 && index < ugyfelek.size());
    }

    Ugyfel* get_ugyfel(int telefonszam){
        size_t i = get_ugyfel_index(telefonszam);
        if(is_valid_ugyfel_index(i)) return ugyfelek[i];

        return nullptr;
    }

    void uj_ugyfel(){
        os << "Uj ugyfel letrehozasa." << endl << "Ugyfel adatai:" << endl;

        int telefonszam = get_number_input("telefonszam", "+36", 1, 9);
        string nev = get_string_input("nev");
        string cim = get_string_input("cim");
        Csomag* csomag = get_csomag_input();

        // check if ugyfel already exists
        // get_ugyfel(telefonszam)
        Ugyfel* ugyfel = get_ugyfel(telefonszam);
        if(ugyfel != nullptr) {
            os << "Ugyfel letrehozasa SIKERTELEN!\n\tMar letetik ugyfel a megadott telefonszammal." << endl;
            return;
        }

        //ugyfelek.push_back(new Ugyfel( static_cast<int>(telefonszam), nev, cim, new AlapCsomag("alap") ));
        //ugyfelek.push_back(new Ugyfel( telefonszam, nev, cim, new AlapCsomag("alap") ));
        ugyfelek.push_back(new Ugyfel( telefonszam, nev, cim, csomag ));
        os << "Ugyfel sikeresen letrehozva." << endl;
    }

    void ugyfel_torlese(){
        os << "Ugyfel torlese." << endl << "Ugyfel adatai:" << endl;

        int telefonszam = get_number_input("telefonszam", "+36", 1, 9);
        string nev = get_string_input("nev");
        string cim = get_string_input("cim");

        size_t ugyfel_index = get_ugyfel_index(telefonszam);
        if( is_valid_ugyfel_index(ugyfel_index) ){
            Ugyfel* ugyfel = ugyfelek[ugyfel_index];
            if( ugyfel->getNev() == nev && ugyfel->getCim() == cim ){
                os << "Ugyfel torlese sikeres!" << endl;
                delete ugyfelek.pop(ugyfel_index);
                return;
            }
        }

        os << "Ugyfel nem talalhato!" << endl;

    }

    void ugyfelek_listazasa(){
        int ugyfelek_szama = ugyfelek.size();
        if(ugyfelek.isEmpty()) { os << "Nincsenek ugyfelek a rendszerben!" << endl; return; }
        os << "Ugyfelek a rendszerben:" << endl;
        for(int i = 0; i < ugyfelek_szama; ++i){
            os << i+1 << ".\ttelefonszam: +36" << ugyfelek[i]->getTel() << endl
                << "\tnev: " << ugyfelek[i]->getNev() << endl
                << "\tcim: " << ugyfelek[i]->getCim() << endl
                << "\tcsomag: " << ugyfelek[i]->getCsomagNev() << endl;
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

            string valasztas = get_string_input("Valasztas");

            valasztas_kezelo(valasztas);
        }
    }

    void valasztas_kezelo(const string& valasztas){
        if     (valasztas == "0") kilep();   // 0. kilep
        else if(valasztas == "1") uj_ugyfel();           // 1. ugyfel felvetele
        else if(valasztas == "2") ugyfelek_listazasa();
        else if(valasztas == "3") ugyfel_torlese();
        else os << "ertelmezhetetlen";
    }

    ~Menu(){
        int ugyfelek_szama = ugyfelek.size();
        for(int i = 0; i < ugyfelek_szama; ++i){
            delete ugyfelek[i];
        }
    }


};

#endif // _MENU
