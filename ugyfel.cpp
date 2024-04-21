#include "ugyfel.h"

void Ugyfel::beolvas(std::istream& is){
    is >> telefonszam >> nev >> cim >> csomag;
}

void Ugyfel::kiir(std::ostream& os){
    //os << "telefonszam: " << telefonszam << "\tnev: "<<  nev << "\tcim: "<< cim << "\tcsomag: "<< csomag;
    os << telefonszam << '\t' << nev << '\t' << cim << '\t' << csomag->getNev();
}

std::ostream& operator<<(std::ostream& os, Ugyfel& u){
    u.kiir(os);
    return os;
}

std::istream& operator>>(std::istream& is, Ugyfel& u){
    u.beolvas(is);
    return is;
}




