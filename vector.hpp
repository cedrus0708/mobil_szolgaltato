/**
 * \file vector.hpp
 *
 * Ez a f�jl tartalmazza a vector oszt�ly deklar�ci�j�t �s inline f�ggv�nyeit.
 */
#ifndef _VECTOR
#define _VECTOR

#include <iostream>

#include "memtrace.h"
#include <exception>


template<typename T>
class vector {
private:

    size_t res;            ///< lefoglalt ter�let

    unsigned int len;   ///< adatok sz�ma
    T* pData;           ///< pointer az adatokra

public:
    /// Default Konstruktor
    inline vector() :res(0), len(0), pData(new T[0]) {};

    /// Konstruktor, m�r el�re foglal helyet.
    /// @param reservation - mennyi helyet foglaljon
    vector(size_t reservation);

    /// Copy Konstruktor
    vector(const vector& v);

    /// Destruktor
    inline ~vector(){ delete[] pData; };


    /// Visszaadja a vektor m�ret�t.
    /// @return mennyi elem van a vektorban
    inline int size() const { return len; };

    /// �res-e a vektor
    /// @return �res-e
    inline bool isEmpty() const { return len == 0; };

    /// Visszaadja, hogy mennyi hely van foglalva �sszesen.
    /// @return foglalt hely
    inline size_t reserved() const { return res; };


    /// Tov�bbi helyet lehet foglani a vektorban.
    /// @param reservation - amennyi helyet szeretn�nk pluszba
    void reserve(size_t reservation);

    /// Aut�matikusan �tm�rezeti �gy a t�mb�t, hogy a feleselegesen foglalt helyeket elhagyja.
    /// A reserve f�ggv�ny "p�rja".
    void resize();

    /// A vektor v�g�hez f�z.
    /// @param new_element - a vektor v�g�hez f�zend� elem
    void push_back(T new_element);

    /// Kivesz egy elemet a vektrob�l.
    /// @param idx - egy �rv�nyes index a vektoron bel�l
    /// @return a kivett elem
    ///     �rv�nytelen index eset�n std::out_of_range t�pus� kiv�telt dob.
    T pop(size_t idx);

    /// Ki�r�ti a vektort
    void clear();


    /// Indexel� oper�tor
    /// @param idx - egy �rv�nyes index a vektorban
    /// @return a vektor indexedik eleme
    ///     Helytelen indexel�s eset�n std::out_of_range kiv�telt dob.
    T& operator[](size_t idx);

    /// Indexel� oper�tor
    /// @param idx - egy �rv�nyes index a vektorban
    /// @return a vektor indexedik eleme
    ///     Helytelen indexel�s eset�n std::out_of_range kiv�telt dob.
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
