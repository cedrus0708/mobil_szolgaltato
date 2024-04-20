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
using std::endl;

int main()
{

    Menu menu;

    menu.fomenu();

    /*std::ifstream myfile("ugyfelek.txt");
    Ugyfel u;
    myfile >> u;
    cout << u.getTel();*/

    return 0;
}
