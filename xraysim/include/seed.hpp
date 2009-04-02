/* 
 * File:   seedstack.hpp
 * Author: uli
 *
 * Created on 1. April 2009, 19:12
 */

#ifndef _SEED_HPP
#define	_SEED_HPP

template<class T>
T generateSeed()
{
    #ifdef __linux__
    T seed;
    FILE* f = fopen("/dev/urandom", "rb");
    fread(&seed, sizeof(T), 1, f);
    fclose(f);
    return seed;
    #else //__linux__
    return (T)time(0);
    #endif //__linux__
}

#endif	/* _SEED_HPP */

