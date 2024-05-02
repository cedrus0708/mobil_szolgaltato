/**
 *
 * \file string.cpp
 *
 */
#include "string.h"
#include "memtrace.h"

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Stringműveletekhez


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

bool string::includes(char c) const {
    for(size_t i = 0; i < length; ++i)
        if(pData[i] == c) return true;
    return false;
}

size_t string::find_first_of(const string& characters) const {
    size_t i = 0;
    if(length)
        while(!characters.includes(pData[i]) && i < length) i++;
    return i;
}

size_t string::find_last_of(const string& characters) const {
    size_t i = size() - 1;
    if(length)
        while(!characters.includes(pData[i]) && i > 0 ) i--;
    return i;
}

size_t string::find_first_not_of(const string& characters) const {
    size_t i = 0;
    if(length)
        while(characters.includes(pData[i]) && i < length ) i++;
    return i;
}

size_t string::find_last_not_of(const string& characters) const {
    size_t i = size() - 1;
    if(length)
        while(characters.includes(pData[i]) && i > 0 ) i--;
    return i;
}

string& string::erase(size_t start) {
    return erase(start, size());
}


string& string::erase(size_t start, size_t stop) {
    if(start < 0 || start > stop || stop > size()) return *this;

    size_t new_length = stop - start;
    char* new_pData = new char[new_length + 1];
    strncpy(new_pData, pData + start, new_length);
    new_pData[new_length] = '\0';
    delete[] pData;
    pData = new_pData;
    length = new_length;
    return *this;
}

string& string::trim(){
    string white_spaces = " \f\n\r\t\v";

    // trim right
    size_t pos = find_last_not_of( white_spaces );
    erase( 0, pos + 1 );

    // trim left
    pos = find_first_not_of( white_spaces );
    erase( pos );

    return *this;
}

string& string::remove_all(char c) {
    size_t new_length = 0;
    for (size_t i = 0; i < length; ++i)
        if(pData[i] != c) new_length++;
    char* new_pData = new char[new_length + 1];
    size_t new_pData_index = 0;
    for (size_t i = 0; i < length; ++i)
        if( pData[i] != c ) new_pData[new_pData_index++] = pData[i];
    delete[] pData;
    pData = new_pData;
    length = new_length;
    return *this;
}

string& string::remove_all(const string& chars) {
    size_t new_length = 0;
    for (size_t i = 0; i < length; ++i)
        if( !chars.includes(pData[i]) ) new_length++;
    char* new_pData = new char[new_length + 1];
    size_t new_pData_index = 0;
    for (size_t i = 0; i < length; ++i)
        if( !chars.includes(pData[i]) ) new_pData[new_pData_index++] = pData[i];
    new_pData[new_pData_index] = '\0';
    delete[] pData;
    pData = new_pData;
    length = new_length;
    return *this;
}



std::ostream& operator<<(std::ostream& os, const string& s){
    os << s.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, string& s){

    char c;
    s = string("");

    while(is.get(c)) {
        if(c != '\n') s = s + c;
        else break;
    }

    return is;

}

int countDigits(int number) {
    int count = 0;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

int stoi(const string& str){
    string str_clone = str;
    str_clone.remove_all(" \f\n\r\t\v");
    int szam = 0;
    sscanf(str_clone.c_str(), "%d", &szam);
    return szam;
}
