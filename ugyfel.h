#ifndef _UGYFEL
#define _UGYFEL

//#include <iostream>
//#include <fstream>

#include "string.h"
#include "csomag.h"


class Ugyfel {

    int telefonszam;
    string nev;
    string cim;

    Csomag* csomag;

public:
    Ugyfel( const int telefonszam = 0, const string& nev = "", const string& cim = "", Csomag* csomag = nullptr) : telefonszam(telefonszam), nev(nev), cim(cim), csomag(csomag) {};

    int getTel() const { return telefonszam; };
    string getNev() const { return nev; };
    string getCim() const { return cim; };

    void beolvas(std::istream& is);
};

std::istream& operator>>(std::istream& is, Ugyfel& u);

#endif // _UGYFEL
