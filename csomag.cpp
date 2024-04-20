#include "csomag.h"

/*HIBAKEZELÉS HA A FÁJL NEM TUDJA MELYIK CSOMAGOT AKARUNK -> HIBA*/

/*std::istream& operator>>(std::istream& is, Csomag& cs){
    cs.beolvas(is);
    return is;
}*/

double AlapCsomag::szamit(int percek, int sms){
    return percek * perc_dij + sms * sms_dij;
}

double MobiNet::szamit(int percek, int sms){
    double ertek = 0;
    ertek += percek * perc_dij;
    if(sms > ingyenes_sms)
        ertek += (sms - ingyenes_sms) * sms_dij;
    return ertek;
}

double SMSMax::szamit(int percek, int sms){
    return percek * perc_dij + sms * sms_dij;
}


std::istream& operator>>(std::istream& is, Csomag*& cs){
    const string AlapCsomagNev = "alap";
    const string MobiNetNev = "mobinet";
    const string SMSMaxNev = "smsmax";

    delete cs;
    string csomag_nev;
    is >> csomag_nev;

    if( csomag_nev == AlapCsomagNev )
        cs = new AlapCsomag(AlapCsomagNev);
    else if( csomag_nev == MobiNetNev )
        cs = new MobiNet(MobiNetNev);
    else if( csomag_nev == SMSMaxNev )
        cs = new SMSMax(SMSMaxNev);
    else
        cs = nullptr;

    return is;
}
