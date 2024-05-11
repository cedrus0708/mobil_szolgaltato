/**
 * \file csomag.h
 *
 * Ez a fájl tartalmazza az abszrakt Csomag osztály deklarációját és leszármazottjait (AlapCsomag, MobiNet, SMSMax).
 */
#ifndef _CSOMAG
#define _CSOMAG

#include <iostream>
#include "string.h"

#include "memtrace.h"

const string AlapCsomagNev = "AlapCsomag";
const string MobiNetNev = "MobiNet";
const string SMSMaxNev = "SMSMax";

class Csomag {
protected:
    const double perc_dij; ///< egy lebeszélt perc ára
    const double sms_dij;  ///< egy sms ára
public:
    /// Konstruktor
    Csomag(const double perc_dij, const double sms_dij) : perc_dij(perc_dij), sms_dij(sms_dij) {};

    /// Visszaadja a csomag nevét.
    virtual string getNev() const = 0;

    /// Visszaadja, az fizetendő mennyiséget.
    /// @param percek - ennyi percet beszélt
    /// @param sms - küldött sms-ek száma
    /// @return fizetendő összeg
    virtual double szamit(const int percek, const int sms) const = 0;

    /// Destruktor
    virtual ~Csomag(){};
};

class AlapCsomag : public Csomag {

public:
    AlapCsomag() : Csomag(10, 40) {};

    inline string getNev() const { return AlapCsomagNev; };

    double szamit(const int percek, const int sms) const;
};

class MobiNet : public Csomag {
    const int ingyenes_sms; ///< ennyi sms-t lehet ingyenesen küldeni
public:
    MobiNet() : Csomag(5, 50), ingyenes_sms(10) {};

    inline string getNev() const { return MobiNetNev; };

    double szamit(const int percek, const int sms) const;
};

class SMSMax : public Csomag {
    static bool ingyenes_az_sms; ///< ingyenes-e az sms jelen pillanatban
public:
    SMSMax() : Csomag(7, 10) {};

    inline string getNev() const { return SMSMaxNev; };

    inline bool getIngyenesSms() const { return ingyenes_az_sms; };
    inline void toggle_sms_ingyenesseg() { ingyenes_az_sms = !ingyenes_az_sms; }

    double szamit(const int percek, const int sms) const;
};

/// Beolvasás
/// A kapott "régi" csomagot felszabadítja!!!
std::istream& operator>>(std::istream& is, Csomag*& cs);

#endif // _CSOMAG
