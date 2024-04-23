#include <iostream>

#include "memtrace.h"

/* MÉG NEM MŰKÖDIK NEGAGTÍV SZÁMOKRA! */
//#include "string.h"

/*HIBAKEZELÉS*/

//#include "ugyfel.h"
#include "menu.h" //<-- interface

//#include <iostream>
//#include <fstream>

using std::cout;
using std::cin;
using std::endl;

int main()
{

    /*
    jelenleg az a gond, hogy hogyan olvassam be a telefonszámot integer-be.
     csináltam egy templatet-ami így bármit be tud olvasni. De szerintem nem ez lesz a megfelelő módszer erre.
     string-ként kell beolvasni, és utána számmá alakítani.
     Ehhez az kell, hogy a stringből el tudjam tüntetni a white-space-ket.
     Ez azért okozott gondt, mert nem akarom a string osztályom tele pakolni ehhez hasonló random függvényekkel, hogy remove_white_spaces.
     Erre megoldás az lenne, hogy úgy csinálom, mint az az std::string-ben is van, de az már iterátorokat igényel a stringen belülre is.
     VAGY MÉGSEM? Csak egy eleje és vége pointer kell neki, amit viszont nem nehéz előhozni!!
      -> MEGOLDÁS: https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
    gn
    */

    Menu menu(cout, cin);

    menu.fomenu();

    /*std::ifstream myfile("ugyfelek.txt");
    Ugyfel u;
    myfile >> u;
    cout << u.getTel();*/

    return 0;
}
