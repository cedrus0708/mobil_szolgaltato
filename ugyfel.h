/**
 * \file ugyfel.h
 *
 * Ez a f�jl tartalmazza az Ugyfel oszt�ly deklar�ci�j�t �s inline f�ggv�nyeit.
 */
#ifndef _UGYFEL
#define _UGYFEL

#include "string.h"
#include "csomag.h"

#include "memtrace.h"


class Ugyfel {

    int telefonszam;    ///< az �gyf�l telefonsz�ma (+36) r�sz ut�n. Egyben egyedi azonos�t�ja is
    string nev;         ///< az �gyf�l neve
    string cim;         ///< az �gyf�l c�me

    Csomag* csomag;     ///< az �gyf�l �ltal ig�nybe vett csomag

public:
    /// (Default) Konstruktor
    Ugyfel( const int telefonszam = 0, const string& nev = "", const string& cim = "", Csomag* csomag = nullptr) : telefonszam(telefonszam), nev(nev), cim(cim), csomag(csomag) {};

    /// Copy Konstruktor
    Ugyfel( const Ugyfel& u );

    /// Desktuktor
    ~Ugyfel(){
        if(csomag != nullptr) delete csomag;
    }

    /// Visszaadja az �gyf�l telefonsz�m�t.
    /// @return �gyf�l telefonsz�ma
    inline int getTel() const { return telefonszam; };

    /// Visszaadja az �gyf�l nev�t.
    /// @return �gyf�l neve
    inline string getNev() const { return nev; };

    /// Vissszaadja az �gyf�l c�m�t.
    /// @return �gyf�l c�me
    inline string getCim() const { return cim; };

    /// Visszaadja az �gyf�l �ltal ig�nybe vett csomag nev�t.
    /// @return �gyf�lhez tartoz� csomag neve (ha nincs akkor "nincs"-et ad vissza)
    string getCsomagNev() const;

    /// Sz�ml�z�skor kisz�molja, hogy mennyit fizet az �gyf�l
    /// @param perc - ennyi percet besz�lt
    /// @param sms - ennyi sms-t k�ld�tt
    /// @return a fizetend� �sszeg
    ///     Ha nincs megadva csomag az �gyf�lhez, �s sz�ml�zni szeretn�nk, akkor egyszer�en 0-t ad vissza.
    double szamlaz(int perc, int sms) const;

    /// Ki�rja az adatokat
    /// @param os - ostream - ide �rja ki az adatait
    void kiir(std::ostream& os) const;

    /// Beolvassa az adatait
    /// @param is - istream - innen olvas
    void beolvas(std::istream& is);

};

/// Glob�lis f�ggv�nyek a ki�r�shoz �s beolvas�shoz
std::ostream& operator<<(std::ostream& os, Ugyfel& u);
std::istream& operator>>(std::istream& is, Ugyfel& u);

#endif // _UGYFEL
