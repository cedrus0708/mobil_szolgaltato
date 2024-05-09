#include <exception>

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
    TEST(String, konstruktorok) {
        string s1;
        EXPECT_EQ((size_t)0, s1.size());
        EXPECT_STREQ("", s1.c_str());

        string s2 = 'a';
        EXPECT_EQ((size_t)1, s2.size());
        EXPECT_STREQ("a", s2.c_str());

        string s3 = "alma";
        EXPECT_EQ((size_t)4, s3.size());
        EXPECT_STREQ("alma", s3.c_str());

        string s4 = 1234;
        EXPECT_EQ((size_t)4, s4.size());
        EXPECT_STREQ("1234", s4.c_str());

        string s5 = -1234;
        EXPECT_EQ((size_t)5, s5.size());
        EXPECT_STREQ("-1234", s5.c_str());

        string s6 = 0;
        EXPECT_EQ((size_t)1, s6.size());
        EXPECT_STREQ("0", s6.c_str());

        string s7 = s3;
        EXPECT_EQ((size_t)4, s7.size());
        EXPECT_STREQ("alma", s7.c_str());

        try {
            EXPECT_THROW_THROW(string s8(nullptr), std::invalid_argument&);
        } catch (std::invalid_argument&) {
        #ifdef CPORTA
            EXPECT_ENVCASEEQ("ORG_ID", p);
        #endif
        }

    } ENDM

    TEST(String, operatorok) {
        string s1 = "alma";
        s1 = "korte";
        EXPECT_EQ((size_t)5, s1.size());
        EXPECT_STREQ("korte", s1.c_str());

        s1 = s1 + "fa";
        EXPECT_EQ((size_t)7, s1.size());
        EXPECT_STREQ("kortefa", s1.c_str());

        s1 += "level";
        EXPECT_EQ((size_t)12, s1.size());
        EXPECT_STREQ("kortefalevel", s1.c_str());

        string s2 = s1 + 'e';
        EXPECT_EQ((size_t)13, s2.size());
        EXPECT_STREQ("kortefalevele", s2.c_str());

        string s3 = "s3";
        string s4 = "s4";
        string s5 = s3 + s4;
        EXPECT_EQ((size_t)4, s5.size());
        EXPECT_STREQ("s3s4", s5.c_str());

        char s = s5[0];
        EXPECT_EQ('s', s);

        const char s_const = s5[0];
        EXPECT_EQ('s', s_const );

        try {
            EXPECT_THROW_THROW(s5[4], std::out_of_range&);
        } catch (std::out_of_range&) {
        #ifdef CPORTA
            EXPECT_ENVCASEEQ("ORG_ID", p);
        #endif
        }

        string s6 = 's' + string("tring");
        EXPECT_STREQ("string", s6.c_str());

        bool hamis = s3 == s4;
        EXPECT_FALSE(hamis);
        s3[1] = '4';
        bool igaz = s3 == s4;
        EXPECT_TRUE(igaz);

        // operator - szeru
        EXPECT_FALSE(s3.isEmpty());
        s3 = "";
        EXPECT_TRUE(s3.isEmpty());

    } ENDM

    TEST(String, alap_funkciok) {

        string s1 = "string1";
        EXPECT_TRUE(s1.includes('r'));
        EXPECT_FALSE(s1.includes('a'));

        string s2 = "aabbccdd";
        EXPECT_EQ((size_t)2, s2.find_first_of("bc"));
        EXPECT_EQ((size_t)s2.size(), s2.find_first_of("e"));

        EXPECT_EQ((size_t)5, s2.find_last_of("bc"));
        EXPECT_EQ((size_t)0, s2.find_last_of("e"));

        EXPECT_EQ((size_t)2, s2.find_first_not_of("aa"));
        EXPECT_EQ((size_t)s2.size(), s2.find_first_not_of(s2));

        EXPECT_EQ((size_t)5, s2.find_last_not_of("dd"));
        EXPECT_EQ((size_t)0, s2.find_last_not_of(s2));

    } ENDM

    TEST(String, extra_funkciok) {
        //           0123456. . . . . . . .
        string s1 = "itt nincs semmi gond";
        s1.erase(4);
        EXPECT_STREQ("nincs semmi gond", s1.c_str());
        s1.erase(6,11);
        EXPECT_STREQ("semmi", s1.c_str());

        string s3 = "  \t string ;\n";
        s3.trim();
        EXPECT_STREQ("string ;", s3.c_str());

        string s4 = "SSSSstring";
        s4.remove_all('S');
        EXPECT_STREQ("string", s4.c_str());
        s4.remove_all("ring");
        EXPECT_STREQ("st", s4.c_str());


        string s5 = "920";
        EXPECT_EQ(920, stoi(s5));

        string s6 = "-920";
        EXPECT_EQ(-920, stoi(s6));

        string s7 = "0001";
        EXPECT_EQ(1, stoi(s7));

        string s8 = "000";
        EXPECT_EQ(0, stoi(s8));


    } ENDM



    // vector
    TEST(Vector, konstruktorok) {
        vector<int> v1;
        EXPECT_EQ(0, v1.size());
        EXPECT_EQ((size_t)0, v1.reserved());


        vector<int> v2(10);
        EXPECT_EQ(0, v2.size());
        EXPECT_EQ((size_t)10, v2.reserved());

        vector<int> v3 = v2;
        EXPECT_EQ(0, v3.size());
        EXPECT_EQ((size_t)10, v3.reserved());

    } ENDM

    TEST(Vector, operatorok) {

        vector<int> v1(10);
        try {
            EXPECT_THROW_THROW(v1[0], std::out_of_range&);
        } catch (std::out_of_range&) {
        #ifdef CPORTA
            EXPECT_ENVCASEEQ("ORG_ID", p);
        #endif
        }

        vector<int> v2 = v1;
        for(int i = 0; i < 10; ++i)
            v1.push_back(i);
        EXPECT_EQ(10, v1.size());
        EXPECT_EQ(0, v2.size());

        EXPECT_EQ(3, v1[3]);
        const int cint = v1[9];
        EXPECT_EQ(9, cint);

        try {
            EXPECT_THROW_THROW(v1[10], std::out_of_range&);
        } catch (std::out_of_range&) {
        #ifdef CPORTA
            EXPECT_ENVCASEEQ("ORG_ID", p);
        #endif
        }

        // operator szeru getterek
        EXPECT_TRUE(v2.isEmpty());
        EXPECT_FALSE(v1.isEmpty());


    } ENDM

    TEST(Vector, funkciok) {
        vector<int> v1;
        for(int i = 0; i < 10; ++i)
            v1.push_back(i);
        EXPECT_EQ(10, v1.size());

        v1.reserve(10);
        EXPECT_EQ(10, v1.size());
        EXPECT_EQ((size_t)20, v1.reserved());

        v1.push_back(10);
        v1.resize();
        EXPECT_EQ(11, v1.size());
        EXPECT_EQ((size_t)11, v1.reserved());

        const int ketto = v1.pop(2);
        EXPECT_EQ(2, ketto);
        EXPECT_EQ(10, v1.size());
        EXPECT_EQ((size_t)11, v1.reserved());
        try {
            EXPECT_THROW_THROW(v1.pop(10), std::out_of_range&);
        } catch (std::out_of_range&) {
        #ifdef CPORTA
            EXPECT_ENVCASEEQ("ORG_ID", p);
        #endif
        }

        v1.clear();
        EXPECT_EQ(0, v1.size());
        EXPECT_EQ((size_t)11, v1.reserved());

        v1.resize();
        EXPECT_EQ(0, v1.size());
        EXPECT_EQ((size_t)0, v1.reserved());
        try {
            EXPECT_THROW_THROW(v1.pop(0), std::out_of_range&);
        } catch (std::out_of_range&) {
        #ifdef CPORTA
            EXPECT_ENVCASEEQ("ORG_ID", p);
        #endif
        }


    } ENDM

   /*
    TEST(String, kivetelek) {


    } ENDM
    */



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




