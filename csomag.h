#ifndef _CSOMAG
#define _CSOMAG

#include <iostream>
#include "string.h"

/*const string AlapCsomagNev = "alap";
const string MobiNetNev = "mobinet";
const string SMSMaxNev = "smsmax";*/

/*COPY CONSTRUCTOR, DESTRUCTOR ?? */
class Csomag {
private:
    const string nev;
protected:
    const double perc_dij;
    const double sms_dij;
public:
    Csomag(const string& nev, const double perc_dij, const double sms_dij) : nev(nev), perc_dij(perc_dij), sms_dij(sms_dij) {};

    string getNev() const { return nev; };

    virtual double szamit(int percek, int sms) = 0;

    virtual ~Csomag(){};
};

class AlapCsomag : public Csomag {

public:
    AlapCsomag(const string& nev) : Csomag(nev, 10, 40) {};

    double szamit(int percek, int sms);


};

class MobiNet : public Csomag {
    int ingyenes_sms;
public:
    MobiNet(const string& nev) : Csomag(nev, 5, 50), ingyenes_sms(10) {};

    double szamit(int percek, int sms);
};

class SMSMax : public Csomag {
public:
    SMSMax(const string& nev) : Csomag(nev, 7, 10) {};

    double szamit(int percek, int sms);
};

/*A kapott csomagot felszabadítja!!!*/
std::istream& operator>>(std::istream& is, Csomag*& cs);

#endif // _CSOMAG
