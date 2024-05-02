/**
 * \file ugyfel.h
 *
 * Ez a fájl tartalmazza az Ugyfel osztály deklarációját és inline függvényeit.
 */
#ifndef _UGYFEL
#define _UGYFEL

#include "string.h"
#include "csomag.h"

#include "memtrace.h"


class Ugyfel {

    int telefonszam;    ///< az ügyfél telefonszáma (+36) rész után. Egyben egyedi azonosítója is
    string nev;         ///< az ügyfél neve
    string cim;         ///< az ügyfél címe

    Csomag* csomag;     ///< az ügyfél által igénybe vett csomag

public:
    /// (Default) Konstruktor
    Ugyfel( const int telefonszam = 0, const string& nev = "", const string& cim = "", Csomag* csomag = nullptr) : telefonszam(telefonszam), nev(nev), cim(cim), csomag(csomag) {};

    /// Copy Konstruktor
    Ugyfel( const Ugyfel& u );

    /// Desktuktor
    ~Ugyfel(){
        if(csomag != nullptr) delete csomag;
    }

    /// Visszaadja az ügyfél telefonszámát.
    /// @return ügyfél telefonszáma
    inline int getTel() const { return telefonszam; };

    /// Visszaadja az ügyfél nevét.
    /// @return ügyfél neve
    inline string getNev() const { return nev; };

    /// Vissszaadja az ügyfél címét.
    /// @return ügyfél címe
    inline string getCim() const { return cim; };

    /// Visszaadja az ügyfél által igénybe vett csomag nevét.
    /// @return ügyfélhez tartozó csomag neve (ha nincs akkor "nincs"-et ad vissza)
    string getCsomagNev() const;

    /// Számlázáskor kiszámolja, hogy mennyit fizet az ügyfél
    /// @param perc - ennyi percet beszélt
    /// @param sms - ennyi sms-t küldött
    /// @return a fizetendõ összeg
    ///     Ha nincs megadva csomag az ügyfélhez, és számlázni szeretnénk, akkor egyszerûen 0-t ad vissza.
    double szamlaz(int perc, int sms) const;

    /// Kiírja az adatokat
    /// @param os - ostream - ide írja ki az adatait
    void kiir(std::ostream& os) const;

    /// Beolvassa az adatait
    /// @param is - istream - innen olvas
    void beolvas(std::istream& is);

};

/// Globális függvények a kiíráshoz és beolvasáshoz
std::ostream& operator<<(std::ostream& os, Ugyfel& u);
std::istream& operator>>(std::istream& is, Ugyfel& u);

#endif // _UGYFEL
