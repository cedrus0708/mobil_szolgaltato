/**
 * \file vector.hpp
 *
 * Ez a fájl tartalmazza a vector osztály deklarációját és inline függvényeit.
 */
#ifndef _VECTOR
#define _VECTOR

#include <iostream>

#include "memtrace.h"


template<typename T>
class vector {
private:

    int res;            ///< lefoglalt terület

    unsigned int len;   ///< adatok száma
    T* pData;           ///< pointer az adatokra

public:
    /// Default Konstruktor
    inline vector() : :res(0), len(0), pData(new T[0]) {};

    /// Konstruktor, már elõre foglal helyet.
    /// @param reservation - mennyi helyet foglaljon
    vector(size_t reservation);

    /// Copy Konstruktor
    vector(const vector& v);

    /// Destruktor
    inline ~vector(){ delete[] pData; };


    /// Visszaadja a vektor méretét.
    /// @return mennyi elem van a vektorban
    inline int size() const { return len; };

    /// Üres-e a vektor
    /// @return üres-e
    inline bool isEmpty() const { return len == 0; };

    /// Visszaadja, hogy mennyi hely van foglalva összesen.
    /// @return foglalt hely
    size_t reserved() const;


    /// További helyet lehet foglani a vektorban.
    /// @param reservation - amennyi helyet szeretnénk pluszba
    void reserve(int reservation);

    /// Autómatikusan átmérezeti úgy a tömböt, hogy a feleselegesen foglalt helyeket elhagyja.
    /// A reserve függvény "párja".
    void resize();

    /// A vektor végéhez fûz.
    /// @param new_element - a vektor végéhez fûzendõ elem
    void push_back(T new_element);

    /// Kivesz egy elemet a vektroból.
    /// @param idx - egy érvényes index a vektoron belül
    /// @return a kivett elem
    ///     Érvénytelen index esetén const char* típusú hibát dob.
    T pop(unsigned int idx);

    /// Kiüríti a vektort
    void clear() {
        len = 0;
        delete[] pData;
        pData = new T[len];
    }


    /// Indexelõ operátor
    /// @param idx - egy érvényes index a vektorban
    /// @return a vektor indexedik eleme
    inline T& operator[](unsigned int idx){ return pData[idx]; }

    /// Indexelõ operátor
    /// @param idx - egy érvényes index a vektorban
    /// @return a vektor indexedik eleme
    inline T operator[](unsigned int idx) const { return pData[idx]; }
};



template<typename T>
vector<T>::vector(const vector& v){
    len = v.len;
    pData = new T[len];
    for(unsigned int i = 0; i < len; ++i)
        pData[i] = v.pData[i];
}

template<typename T>
void vector<T>::push_back(T new_element){
    T* new_pData = new T[len + 1];
    for(unsigned int  i = 0; i < len; ++i)
        new_pData[i] = pData[i];
    new_pData[len++] = new_element;
    delete[] pData;
    pData = new_pData;
}

template<typename T>
T vector<T>::pop(unsigned int idx) {
    if(idx < 0 || idx >= len) throw "vector: index error";
    T* new_pData = new T[--len];
    for(unsigned int  i = 0; i < idx; ++i){
        new_pData[i] = pData[i];
    }
    T ret_v = pData[idx];
    for(unsigned int i = idx + 1; i < len + 1; ++i){
        new_pData[i -1 ] = pData[i];
    }
    delete[] pData;
    pData = new_pData;
    return ret_v;
}

#endif // _VECTOR
