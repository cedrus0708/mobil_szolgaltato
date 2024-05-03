#include <iostream>
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

    Interface interface(std::cout, std::cin);
    interface.run();

#endif // TESZT



    return 0;
}
