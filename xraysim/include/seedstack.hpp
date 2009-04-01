/* 
 * File:   seedstack.hpp
 * Author: uli
 *
 * Created on 1. April 2009, 19:12
 */

#ifndef _SEEDSTACK_HPP
#define	_SEEDSTACK_HPP
#include <stack>
#include <tr1/random>

using namespace std;
using namespace std::tr1;

template <class T>
class SeedStack
{
public:
    SeedStack (int num = 10);
    ~SeedStack ();
    T pop ();
private:
    /**
     * Array containing the seeds
     * Size specified at runtime
     */
    T* data;
    /**
     * The next index to be returned
     */
    int index;
    /**
     * The number of elements in the array
     */
    int size;

    /**
     * Generates a cryptographic seed
     * Source on *NIX systems: /dev/urandom
     * Other systems: CryptGenRandom()
     */
    void refreshSeeds ();
};
#endif	/* _SEEDSTACK_HPP */

