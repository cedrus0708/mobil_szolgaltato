/**
 *
 * \file interface.cpp
 *
 */
#include "interface.h"
#include "memtrace.h"

#include <iostream>
#include <fstream>

using std::endl;


string Interface::read_input(const string& input_name, const string& input_start_text){
    os << '\t' << input_name << ": " << input_start_text;
    string input;
    is >> std::skipws >> input;
    return input;
};

string Interface::get_string_input(const string& input_name, const string& input_start_text, const size_t min_length, const size_t max_length){
    string text = read_input(input_name, input_start_text).trim();
    while(text.size() < min_length || text.size() > max_length ) {
        os << "\t\tNem megfelelo bemenet.";
        if(text.size() < min_length) os << " (elvart hossz legalabb " << min_length << ')' << endl;
        else os << " (elvart hossz maximum " << max_length << ')' << endl;
        text = read_input(input_name, input_start_text).trim();
    }
    return text;
}


Csomag* Interface::get_csomag_input(){
    Csomag* csomag;

    int csomag_szam = 0;
    while( csomag_szam > 3 || csomag_szam < 1){
        os << "\tcsomag:" << endl
            << "\t\t1. " << AlapCsomagNev << endl
            << "\t\t2. " << MobiNetNev << endl
            << "\t\t3. " << SMSMaxNev << endl;
        csomag_szam = get_number_input("\t\tcsomag szama", "", 1, 1);

        if(csomag_szam == 1) csomag = new AlapCsomag();
        else if(csomag_szam == 2) csomag = new MobiNet();
        else if(csomag_szam == 3) csomag = new SMSMax();
    }

    return csomag;
}

int Interface::get_number_input(const string& input_name, const string& input_start_text, const size_t min_length, const size_t max_length){
    int number = stoi(read_input(input_name, input_start_text));
    size_t number_length = countDigits(number);
    while(number_length > max_length || number_length < min_length) {
            os << "\t\tNem megfelelo bemenet. (elvart bemenet hossza: " << min_length << '-' << max_length << ")(szamok)" << endl;
            number = stoi(read_input(input_name, input_start_text));  number_length = countDigits(number);
    }
    return number;
}

void Interface::kilep(){
    os << "Kilepes a programbol..." << endl;
    interfacing = false;
}

size_t Interface::get_ugyfel_index(int telefonszam){
    size_t ugyfelek_szama = ugyfelek.size();
    for(size_t i = 0; i < ugyfelek_szama; ++i){
        if(ugyfelek[i]->getTel() == telefonszam)
            return i;
    }
    return ugyfelek_szama;
}

bool Interface::is_valid_ugyfel_index(int index){
    return (index >= 0 && index < ugyfelek.size());
}

Ugyfel* Interface::get_ugyfel(int telefonszam){
    size_t i = get_ugyfel_index(telefonszam);
    if(is_valid_ugyfel_index(i)) return ugyfelek[i];

    return nullptr;
}

void Interface::uj_ugyfel(){
    os << "Uj ugyfel letrehozasa." << endl << "Ugyfel adatai:" << endl;

    int telefonszam = get_number_input("telefonszam", "+36", 1, 9);
    string nev = get_string_input("nev");
    string cim = get_string_input("cim");
    Csomag* csomag = get_csomag_input();

    // check if ugyfel already exists
    // get_ugyfel(telefonszam)
    Ugyfel* ugyfel = get_ugyfel(telefonszam);
    if(ugyfel != nullptr) {
        os << "Ugyfel letrehozasa SIKERTELEN!\n\tMar letezik ugyfel a megadott telefonszammal." << endl;
        return;
    }

    //ugyfelek.push_back(new Ugyfel( static_cast<int>(telefonszam), nev, cim, new AlapCsomag("alap") ));
    ugyfelek.push_back(new Ugyfel( telefonszam, nev, cim, csomag ));
    os << "Ugyfel sikeresen letrehozva." << endl;
}

void Interface::ugyfel_torlese(){
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

void Interface::ugyfelek_listazasa(){
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

void Interface::ugyfelek_fajlba(){
    os << "Ugyfelek fajlba irasa." << endl;
    string file_name = get_string_input("fajlnev") + ".txt";
    std::ofstream file(file_name.c_str());
    // hiba kezeles file.is_open()
    int ugyfelek_szama = ugyfelek.size();

    file << ugyfelek_szama << endl;
    for(int i = 0; i < ugyfelek_szama; ++i){
        ugyfelek[i]->kiir(file); file << endl;
    }
}

void Interface::ugyfelek_fajlbol(){
    os << "Ugyfelek fajbol olvasasa. A regi adatok felul irasra kerulnek!" << endl;
    string file_name = get_string_input("fajlnev") + ".txt";
    std::ifstream file(file_name.c_str());
    if(!file.is_open()) { // THROW
       os << "A megadott fajl nem talalhato! (" << file_name << ")" << endl; return;
    }
    ugyfelek.clear();

    int ugyfelek_szama; file >> ugyfelek_szama;
    for(int i = 0; i < ugyfelek_szama; ++i){
        Ugyfel* new_ugyfel = new Ugyfel();
        file >> (*new_ugyfel);
        ugyfelek.push_back(new_ugyfel);
    }
}

void Interface::szamlazas(){
    os << "Szamlazas." << endl;
    int ugyfelek_szama = ugyfelek.size();
    if(!ugyfelek_szama){ os << "Nincsenek ugyfelek a rendszerben!" << endl; return; }
    os << "Add meg az ugyfelek tovabbi adatait tartalmazo falj nevet!" << endl;
    string file_name = get_string_input("fajlnev") + ".txt";
    std::ifstream file(file_name.c_str());
    if(!file.is_open()) { // THROW
       os << "A megadott fajl nem talalhato! (" << file_name << ")" << endl; return;
    }

    int ugyfelek_szama_fajl; file >> ugyfelek_szama_fajl;
    if(ugyfelek_szama != ugyfelek_szama_fajl){ // THROW
        os << "A fajl tartalma nem megfelelo. (elter az ugyfelek szama)" << endl; return;
    }
    for(int i = 0; i < ugyfelek_szama; ++i){
        int telefonszam, percek, sms; file >> telefonszam >> percek >> sms;
        Ugyfel* ugyfel = get_ugyfel(telefonszam); // throw
        if(!ugyfel) {
            os << "A fajlban ismeretlen ugyfel telefonszama van!" << endl; return;
        }
        os << ugyfel->getNev() << ": " << ugyfel->szamlaz(percek, sms) << "Ft" << endl; // throw
    }
}

void Interface::fomenu(){
    os << endl << "Valassz az alabbi lehetosegek kozul!" << endl;
    os << "0. Kiepes a programbol" << endl
        << "1. Ugyfel felvetele" << endl
        << "2. Ugyfelek listazasa" << endl
        << "3. Ugyfel torlese" << endl
        << "4. Ugyfelek fajlba irasa" << endl
        << "5. Ugyfelek betoltese fajlbol" << endl
        << "6. Szamlazas" << endl;
}

void Interface::run(){ // main_menu
    while(interfacing){
        fomenu();

        string valasztas = get_string_input("Valasztas");

        valasztas_kezelo(valasztas);
    }
}

void Interface::valasztas_kezelo(const string& valasztas){
    if     (valasztas == "0") kilep();                  // 0. kilep
    else if(valasztas == "1") uj_ugyfel();              // 1. ugyfel felvetele
    else if(valasztas == "2") ugyfelek_listazasa();     // 2. ugyfelek listazasa
    else if(valasztas == "3") ugyfel_torlese();         // 3. ugyfelek torlese
    else if(valasztas == "4") ugyfelek_fajlba();        // 4. ugyfelek fajlba irasa
    else if(valasztas == "5") ugyfelek_fajlbol();       // 5. ugyfelek fajlbol ovasasa
    else if(valasztas == "6") szamlazas();              // 6. szamlazas
    else os << "ertelmezhetetlen";
}

Interface::~Interface(){
    int ugyfelek_szama = ugyfelek.size();
    for(int i = 0; i < ugyfelek_szama; ++i){
        delete ugyfelek[i];
    }
}

