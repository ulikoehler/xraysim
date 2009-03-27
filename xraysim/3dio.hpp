/* 
 * File:   3dio.hpp
 * Author: uli
 *
 * Created on 26. März 2009, 19:45
 */

#ifndef _3DIO_HPP
#define	_3DIO_HPP

#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>

#define FIELD_DELIM ',' //Character that separates 2 values

using namespace std;
using namespace boost;

/**
 * Reads digits from the supplied input stream until FIELD_DELIM (constant)
 * is read and returns the digits converted into a number
 * \param in The input stream to read from
 * \return The converted number
 */
template<class T>
inline T
readNextVal (std::istream& in)
{
    static string buffer; //Buffers the digits read from in
    static char c;
    buffer = "";

    while (true) //Break condition: return...
        {
            in.get (c);

            //Check if the char read in is an number
            //(Checks if the character is in the ASCII digit range
            if (c >= '0' && c <= '9')
                {
                    buffer += c;
                }
            else if (c == FIELD_DELIM) //Last character of the field
                {
                    return boost::lexical_cast<T>(buffer);
                }
            }
}

#endif	/* _3DIO_HPP */

