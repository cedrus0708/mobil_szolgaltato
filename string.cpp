/**
 *
 * \file string.cpp
 *
 */

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Stringműveletekhez

#include "memtrace.h"
#include "string.h"


string::string(char c) :length(1), pData(new char[2]) {
    pData[0] = c;
    pData[1] = '\0';
}

string::string(const char* p) {
    if(p == nullptr) throw "string: null pointer a konstruktorban";
    length = strlen(p);
    pData = new char[length + 1];
    strcpy(pData, p);
}

string::string(int value){
    length = countDigits(value);
    pData = new char[length + 1];
    for (int i = length - 1; i >= 0; i--) {
        pData[i] = '0' + (value % 10);
        value /= 10;
    }
    pData[length] = '\0';
};


string::string(const string& str) : length(str.length), pData(new char[length + 1]) {
    strcpy(pData, str.pData);
}



string& string::operator=(const string& rhs_s){
    if(this != &rhs_s){
        delete[] pData;
        length = rhs_s.length;
        pData = new char[length + 1];
        strcpy(pData, rhs_s.pData);
    }
    return *this;
}

string string::operator+(const string& rhs_s) const {
    string new_string;
    delete[] new_string.pData;
    new_string.length = this->length + rhs_s.length;
    new_string.pData = new char[new_string.length + 1];
    strcpy(new_string.pData, this->pData);
    strcpy(new_string.pData + this->length, rhs_s.pData);
    return new_string;
}

char& string::operator[](unsigned int idx){
    if(idx < 0 || idx >= length) throw "string: indexelési hiba";
    return pData[idx];
}

const char& string::operator[](unsigned int idx) const {
    if(idx < 0 || idx >= length) throw "string: indexelési hiba";
    return pData[idx];
}

bool string::operator==(const string& cmp) const {
    if(cmp.length != length) return false;
    return strcmp(pData, cmp.pData) == 0;
}



std::ostream& operator<<(std::ostream& os, const string& s0){
    os << s0.c_str();
    return os;
}

/// Beolvas az istream-rõl egy szót egy string-be.
/// @param is - istream típusú objektum
/// @param s0 - string, amibe beolvas
/// @return is
std::istream& operator>>(std::istream& is, string& s0){
    unsigned char ch;
    s0 = string("");
	std::ios_base::fmtflags fl = is.flags();
	is.setf(std::ios_base::skipws);
    while (is >> ch) {
	    is.unsetf(std::ios_base::skipws);
        if (isspace(ch)) {
            is.putback(ch);
            break;
        } else {
            s0 = s0 + ch;
        }
    }
	is.setf(fl);
    return is;
}

int string::countDigits(int number) {
        int count = 0;
        while (number != 0) {
            number /= 10;
            count++;
        }
        return count;
    }
