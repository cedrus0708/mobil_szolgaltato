#include <iostream>
#include <exception>
#include "memtrace.h"
#include "interface.h"

/// A TESZT makróval lehet állítani, hogy a program teszteljen, vagy normálisan fusson.
/// TESZT = 0 -> nem tesztel
/// TESZT > 0 -> tesztel
#define TESZT 0

#if TESZT
#include "tester.h"
#endif // TESZT

int main()
{

#if TESZT   // ha a TESZT makró definiálva van, tesztel a program

    run_tests();

#else       // ha a TESZT makró nincs definiálva , a program "production" módban fut

    try{

        Interface interface(std::cout, std::cin);
        interface.run();

    }
    catch( const std::exception& error ){
        std::cout << "Vegzetes hiba lepett fel a program futasa soran" << std::endl << error.what();
    }
    catch(...){
        std::cout << "Vegzetes ismeretlen hiba lepett fel!";
    }


#endif // TESZT



    return 0;
}
