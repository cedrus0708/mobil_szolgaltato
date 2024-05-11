/**
 *
 * \file ugyfel.cpp
 *
 */
#include "ugyfel.h"
#include "memtrace.h"

string Ugyfel::getCsomagNev() const {
    if(csomag != nullptr)
        return csomag->getNev();
    return "nincs";
}

double Ugyfel::szamlaz(const int perc, const int sms) const {
    if(csomag == nullptr) return 0;
    return csomag->szamit(perc, sms);
}

void Ugyfel::kiir(std::ostream& os) const {
    os << telefonszam << std::endl << nev << std::endl << cim << std::endl << csomag->getNev();
}

void Ugyfel::beolvas(std::istream& is) {
    is >> telefonszam; is.get(); // sz�m �s sorlez�r�s
    is >> nev >> cim >> csomag;  // tov�bbi adatok
}


std::ostream& operator<<(std::ostream& os, Ugyfel& u) {
    u.kiir(os);
    return os;
}

std::istream& operator>>(std::istream& is, Ugyfel& u) {
    u.beolvas(is);
    return is;
}




