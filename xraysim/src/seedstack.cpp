/* 
 * File:   seedstack.cpp
 * Author: uli
 * 
 * Created on 1. April 2009, 19:12
 */

#include "../include/seedstack.hpp"

template <class T>
SeedStack<T>::SeedStack (int num)
{
    data = new T[num];
    size = num;
    refreshSeeds ();
}

template <class T>
SeedStack<T>::~SeedStack ()
{
    delete[] data;
}

template <class T>
T SeedStack<T>::pop()
{
    T t;
    return t;
}

/**
 * Define
 */
#ifdef __linux__
template <class T>
void
SeedStack<T>::refreshSeeds ()
{
    static T seed;
    FILE* f = fopen ("/dev/urandom", "rb");
    fread (&seed, sizeof (T), this->size, f);
    fclose (f);
}

#else //__linux__

#include <windows.h>
#include <Wincrypt.h>

template <class T>
void
SeedStack<T>::refreshSeeds ()
{
    HCRYPTPROV   hCryptProv;
    CryptGenRandom(hCryptProv, this->size * sizeof(T), this->data);
}

#endif //__linux