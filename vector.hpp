/**
 * \file vector.hpp
 *
 * Ez a fájl tartalmazza a vector osztály deklarációját és inline függvényeit.
 */
#ifndef _VECTOR
#define _VECTOR

#include <iostream>

#include "memtrace.h"
#include <exception>


template<typename T>
class vector {
private:

    size_t res;            ///< lefoglalt terület

    unsigned int len;   ///< adatok száma
    T* pData;           ///< pointer az adatokra

public:
    /// Default Konstruktor
    inline vector() :res(0), len(0), pData(new T[0]) {};

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
    inline size_t reserved() const { return res; };


    /// További helyet lehet foglani a vektorban.
    /// @param reservation - amennyi helyet szeretnénk pluszba
    void reserve(size_t reservation);

    /// Autómatikusan átmérezeti úgy a tömböt, hogy a feleselegesen foglalt helyeket elhagyja.
    /// A reserve függvény "párja".
    void resize();

    /// A vektor végéhez fûz.
    /// @param new_element - a vektor végéhez fûzendõ elem
    void push_back(T new_element);

    /// Kivesz egy elemet a vektroból.
    /// @param idx - egy érvényes index a vektoron belül
    /// @return a kivett elem
    ///     Érvénytelen index esetén std::out_of_range típusú kivételt dob.
    T pop(size_t idx);

    /// Kiüríti a vektort
    void clear();


    /// Indexelõ operátor
    /// @param idx - egy érvényes index a vektorban
    /// @return a vektor indexedik eleme
    ///     Helytelen indexelés esetén std::out_of_range kivételt dob.
    T& operator[](size_t idx);

    /// Indexelõ operátor
    /// @param idx - egy érvényes index a vektorban
    /// @return a vektor indexedik eleme
    ///     Helytelen indexelés esetén std::out_of_range kivételt dob.
    T operator[](size_t idx) const;

};



template<typename T>
vector<T>::vector(size_t reservation) :res(reservation), len(0), pData(new T[reservation]) {}

template<typename T>
vector<T>::vector(const vector& v){
    res = v.res;
    len = v.len;
    pData = new T[res];
    for(unsigned int i = 0; i < len; ++i)
        pData[i] = v.pData[i];
}

template<typename T>
void vector<T>::reserve(size_t reservation){
    res += reservation;
    T* new_pData = new T[res];
    for(size_t i = 0; i < len; ++i)
        new_pData[i] = pData[i];
    delete[] pData;
    pData = new_pData;
}

template<typename T>
void vector<T>::resize(){
    res = len;
    T* new_pData = new T[len];
    for(size_t i = 0; i < len; ++i)
        new_pData[i] = pData[i];
    delete[] pData;
    pData = new_pData;
}

template<typename T>
void vector<T>::push_back(T new_element){
    if(len == res){
        res++;
        T* new_pData = new T[res];
        for(unsigned int  i = 0; i < len; ++i)
            new_pData[i] = pData[i];
        delete[] pData;
        pData = new_pData;
    }
    pData[len++] = new_element;
}

template<typename T>
T vector<T>::pop(size_t idx) {
    if(idx < 0 || idx >= len) throw std::out_of_range("vector: index error");
    T* new_pData = new T[--len];
    for(unsigned int  i = 0; i < idx; ++i){
        new_pData[i] = pData[i];
    }
    T ret_v = pData[idx];
    for(unsigned int i = idx + 1; i < len + 1; ++i){
        new_pData[i - 1] = pData[i];
    }
    delete[] pData;
    pData = new_pData;
    return ret_v;
}

template<typename T>
void vector<T>::clear() {
    len = 0;
    delete[] pData;
    pData = new T[len];
}

template<typename T>
T& vector<T>::operator[](size_t idx){
    if(!len || idx >= len) throw std::out_of_range("vector: index error");
    return pData[idx];
}

template<typename T>
T vector<T>::operator[](size_t idx) const {
    if(!len || idx >= len) throw std::out_of_range("vector: index error");
    return pData[idx];
}


#endif // _VECTOR
