#include "tester.h"
#include "memtrace.h"

#include "string.h"
#include "vector.hpp"
#include "csomag.h"
#include "ugyfel.h"
#include "interface.h"

void run_tests(){
    GTINIT(std::cin);       // Csak C(J)PORTA mûködéséhez kell

    // string
    TEST(String, sanity) {
        string s;
        EXPECT_EQ((size_t)0, s.size()) << "Nem ures?" << std::endl;
        // ...
    } ENDM
    //...

    // vector
    // ...

    // csomag
    // ...

    // ugyfel
    // ...

    // interface
    // ...

    GTEND(std::cerr);       // Csak C(J)PORTA mûködéséhez kell
}

/*void teszt_string(){}

void teszt_vector(){}

void teszt_csomag(){}

void teszt_ugyfel(){}

void teszt_interface(){}*/




