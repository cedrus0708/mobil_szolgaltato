#include "ugyfel.h"

void Ugyfel::beolvas(std::istream& is){
    is >> telefonszam >> nev >> cim >> csomag;
}

std::istream& operator>>(std::istream& is, Ugyfel& u){
    u.beolvas(is);
    return is;
}
