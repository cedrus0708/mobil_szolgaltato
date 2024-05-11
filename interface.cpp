/**
 *
 * \file interface.cpp
 *
 */
#include "interface.h"
#include "memtrace.h"

#include <iostream>
#include <fstream>

#include <stdexcept>

using std::endl;
using std::runtime_error;


string Interface::read_input(const string& input_name, const string& input_start_text) const {
    os << '\t' << input_name << ": " << input_start_text;
    string input;
    is >> std::skipws >> input;
    return input;
};


string Interface::get_string_input(const string& input_name, const string& input_start_text, const size_t min_length, const size_t max_length) const {
    string text = read_input(input_name, input_start_text).trim();
    while(text.size() < min_length || text.size() > max_length ) {
        os << "\t\tNem megfelelo bemenet.";
        if(text.size() < min_length) os << " (elvart hossz legalabb " << min_length << ')' << endl;
        else os << " (elvart hossz maximum " << max_length << ')' << endl;
        text = read_input(input_name, input_start_text).trim();
    }
    return text;
}

int Interface::get_number_input(const string& input_name, const string& input_start_text, const size_t min_length, const size_t max_length, const int min_value, const int max_value ) const {
    int number = stoi(read_input(input_name, input_start_text));
    size_t number_length = countDigits(number);
    while(number_length > max_length || number_length < min_length || number > max_value || number < min_value) {
            os << "\t\tNem megfelelo bemenet. (elvart bemenet hossza: " << min_length << '-' << max_length << ")(szamok)";
            if(number > max_value)
               os << "(maximum:"<<max_value<<")";
            if(number < min_value)
               os << "(minimum:"<<min_value<<")";
            os << endl;
            number = stoi(read_input(input_name, input_start_text));  number_length = countDigits(number);
    }
    return number;
}

Csomag* Interface::get_csomag_input() const {
    Csomag* csomag;

    int csomag_szam = 0;
    while( csomag_szam > 3 || csomag_szam < 1){
        os << "\tcsomag:" << endl
            << "\t\t1. " << AlapCsomagNev << endl
            << "\t\t2. " << MobiNetNev << endl
            << "\t\t3. " << SMSMaxNev << endl;
        csomag_szam = get_number_input("\t\tcsomag szama", "", 1, 1, 1, 3);

        if(csomag_szam == 1) csomag = new AlapCsomag();
        else if(csomag_szam == 2) csomag = new MobiNet();
        else if(csomag_szam == 3) csomag = new SMSMax();
        else os << "\t\tNincs ilyen menupont!" << endl;
    }

    return csomag;
}



void Interface::delete_ugyfelek(){
    int ugyfelek_szama = ugyfelek.size();
    for(int i = 0; i < ugyfelek_szama; ++i){
        delete ugyfelek[i];
    }
    ugyfelek.clear();
}



bool Interface::is_valid_ugyfel_index(const int index) const {
    return (index >= 0 && index < ugyfelek.size());
}

size_t Interface::get_ugyfel_index(const int telefonszam) const {
    size_t ugyfelek_szama = ugyfelek.size();
    for(size_t i = 0; i < ugyfelek_szama; ++i){
        if(ugyfelek[i]->getTel() == telefonszam)
            return i;
    }
    return ugyfelek_szama;
}

Ugyfel* Interface::get_ugyfel(const int telefonszam) const {
    size_t i = get_ugyfel_index(telefonszam);
    if(is_valid_ugyfel_index(i)) return ugyfelek[i];

    return nullptr;
}



void Interface::fomenu() const {

    SMSMax smsmax;
    bool bool_test_free = smsmax.getIngyenesSms();

    os << endl << "Valassz az alabbi lehetosegek kozul!" << endl;
    os << "0. Kiepes a programbol" << endl
        << "1. Ugyfel felvetele" << endl
        << "2. Ugyfelek listazasa" << endl
        << "3. Ugyfel torlese" << endl
        << "4. Ugyfelek fajlba irasa" << endl
        << "5. Ugyfelek betoltese fajlbol" << endl
        << "6. Szamlazas" << endl
        << "7. SMSMax sms: " << (bool_test_free ? "ingyenes" : "fizetos") << endl;
}

void Interface::valasztas_kezelo(const string& valasztas) {
    try {

        if     (valasztas == "0") kilep();                  // 0. kilep
        else if(valasztas == "1") uj_ugyfel();              // 1. ugyfel felvetele
        else if(valasztas == "2") ugyfelek_listazasa();     // 2. ugyfelek listazasa
        else if(valasztas == "3") ugyfel_torlese();         // 3. ugyfelek torlese
        else if(valasztas == "4") ugyfelek_fajlba();        // 4. ugyfelek fajlba irasa
        else if(valasztas == "5") ugyfelek_fajlbol();       // 5. ugyfelek fajlbol ovasasa
        else if(valasztas == "6") szamlazas();              // 6. szamlazas
        else if(valasztas == "7") sms_teszt_toggle();       // 7. smsmax csomag állítása
        else os << "Nincs ilyen menupont!";

    }
    catch( const runtime_error& e ){
        os << "Hiba tortent:" << endl << e.what() << endl;
    }
}



void Interface::kilep(){
    os << "Kilepes a programbol..." << endl;
    interfacing = false;
}

void Interface::uj_ugyfel(){
    os << "Uj ugyfel letrehozasa." << endl << "Ugyfel adatai:" << endl;

    // adatok bekérése
    int telefonszam = get_number_input("telefonszam", "+36", 1, 9, 1);
    string nev = get_string_input("nev");
    string cim = get_string_input("cim");
    Csomag* csomag = get_csomag_input();

    // létezik-e már az ügyfél
    Ugyfel* ugyfel = get_ugyfel(telefonszam);
    if(ugyfel != nullptr) {
        delete csomag;
        throw runtime_error("Ugyfel letrehozasa SIKERTELEN!\n\tMar letezik ugyfel a megadott telefonszammal.");
    }

    //ugyfelek.push_back(new Ugyfel( static_cast<int>(telefonszam), nev, cim, new AlapCsomag("alap") ));
    ugyfelek.push_back(new Ugyfel( telefonszam, nev, cim, csomag ));
    os << "Ugyfel sikeresen letrehozva." << endl;
}

void Interface::ugyfelek_listazasa() const {
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

void Interface::ugyfel_torlese(){
    os << "Ugyfel torlese." << endl << "Ugyfel adatai:" << endl;

    int telefonszam = get_number_input("telefonszam", "+36", 1, 9, 1);
    string nev = get_string_input("nev");
    string cim = get_string_input("cim");

    size_t ugyfel_index = get_ugyfel_index(telefonszam);
    if( is_valid_ugyfel_index(ugyfel_index) ){
        Ugyfel* ugyfel = ugyfelek[ugyfel_index];
        if( ugyfel->getNev() == nev && ugyfel->getCim() == cim ){
            delete ugyfelek.pop(ugyfel_index);
            os << "Ugyfel torlese sikeres!" << endl;
            return;
        }
    }

    throw runtime_error("Ugyfel nem talalhato!");

}

void Interface::ugyfelek_fajlba() const {
    os << "Ugyfelek fajlba irasa." << endl;
    string file_name = get_string_input("fajlnev") + ".txt";
    std::ofstream file(file_name.c_str());

    if(file.fail()) throw runtime_error("A fajl megnyitasa sikertelen!");

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
    if(!file.is_open()) {
        throw runtime_error(string("A megadott fajl nem talalhato! (" + file_name + ")").c_str());
    }

    delete_ugyfelek();

    int ugyfelek_szama; file >> ugyfelek_szama;
    for(int i = 0; i < ugyfelek_szama; ++i){
        Ugyfel* new_ugyfel = new Ugyfel();
        file >> (*new_ugyfel);
        ugyfelek.push_back(new_ugyfel);
    }
}

string Interface::szamlazas_szamol(std::ifstream& source_file, std::ostream& os) const {
    int ugyfelek_szama = ugyfelek.size();

    int ugyfelek_szama_fajl; source_file >> ugyfelek_szama_fajl;
    if(ugyfelek_szama != ugyfelek_szama_fajl){ // THROW
        throw runtime_error("A fajl tartalma nem megfelelo. (elter az ugyfelek szama)");
    }

    for(int i = 0; i < ugyfelek_szama; ++i){
        int telefonszam = 0, percek = 0, sms = 0; source_file >> telefonszam >> percek >> sms;
        if(telefonszam == 0) throw runtime_error("Hibas a fajl tartalma!");
        Ugyfel* ugyfel = get_ugyfel(telefonszam); // throw
        if(!ugyfel) {
            throw runtime_error("A fajlban ismeretlen ugyfel telefonszama van!");
        }
        os << ugyfel->getNev() << ": " << ugyfel->szamlaz(percek, sms) << "Ft" << endl; // throw
    }

    return "A szamazas sikeresen veget ert.";

}

void Interface::szamlazas() const {
    os << "Szamlazas." << endl;

    if(!ugyfelek.size()){ os << "Nincsenek ugyfelek a rendszerben!" << endl; return; }

    os << "Add meg az ugyfelek tovabbi adatait tartalmazo falj nevet!" << endl;
    string source_file_name = get_string_input("fajlnev") + ".txt";
    std::ifstream source_file(source_file_name.c_str());
    if(!source_file.is_open()) { // THROW
       throw runtime_error(string("A megadott fajl nem talalhato! (" + source_file_name + ")").c_str());
    }

    string result;
    os << "Add meg, hova irja a rendszer a szamlazas eredmenyet! (opcionalis)" << endl;
    string target_file_name = get_string_input("fajlnev", "", 0);
    if( !target_file_name.isEmpty() ){
        target_file_name = target_file_name + ".txt";
        if(source_file_name == target_file_name){
            throw runtime_error("Nem lehet a forras es a cel falj azonos!");
        }
        std::ofstream target_file(target_file_name.c_str());
        if(target_file.fail()) throw runtime_error("A faljt nem sikerült megnyitni!");

        result = szamlazas_szamol( source_file, target_file );
        os << "Az eredmenyek a " << source_file_name << " allomanyban talalhato." << endl;
    } else {
        result = szamlazas_szamol( source_file, os );
    }

    os << result << endl;
}

void Interface::sms_teszt_toggle() const {

    os << "\tAtallitva!" << endl;

    SMSMax smsmax;
    smsmax.toggle_sms_ingyenesseg();

}



Interface::~Interface(){
    delete_ugyfelek();
}



void Interface::run(){
    while(interfacing){
        fomenu();

        string valasztas = get_string_input("Valasztas");

        valasztas_kezelo(valasztas);
    }
}
