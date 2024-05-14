/**
 *
 * \file csomag.cpp
 *
 */
#include "csomag.h"
#include "memtrace.h"


bool SMSMax::ingyenes_az_sms = false;


double AlapCsomag::szamit(const int percek, const int sms) const {
    return percek * perc_dij + sms * sms_dij;
}

double MobiNet::szamit(const int percek, const int sms) const {
    double ertek = 0;
    ertek += percek * perc_dij;
    if(sms > ingyenes_sms)
        ertek += (sms - ingyenes_sms) * sms_dij;
    return ertek;
}

double SMSMax::szamit(const int percek, const int sms) const {
    double ertek = percek * perc_dij;
    if(!ingyenes_az_sms)
        ertek += sms * sms_dij;
    return ertek;
}


std::istream& operator>>(std::istream& is, Csomag*& cs){

    delete cs;
    string csomag_nev;
    is >> csomag_nev;

    if( csomag_nev == AlapCsomagNev )
        cs = new AlapCsomag();
    else if( csomag_nev == MobiNetNev )
        cs = new MobiNet();
    else if( csomag_nev == SMSMaxNev )
        cs = new SMSMax();
    else
        cs = nullptr;

    return is;
}
