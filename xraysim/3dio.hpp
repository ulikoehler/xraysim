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
#include <boost/multi_array.hpp>

//Typedefs
typedef boost::multi_array<uint32_t, 3> matrix3d;

//Constant decs
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
            if(c == '.') //Append the decimal separator
                {
                    buffer += c;
                }
            else if (c == FIELD_DELIM) //Last character of the field
                {
                    return boost::lexical_cast<T>(buffer);
                }
            }
}

/**
 * Reads in a multi-dimensional array
 * Toplevel function, so no template needed (at least yet)
 * \param x The x extent
 * \param y The y extent
 * \param z The z extent
 * \param in The istream to read the data from
 */
inline matrix3d readMatrix3d(uint x, uint y, uint z, std::istream& in)
{
    matrix3d retMatrix(boost::extents[x][y][z]);

    for(int ix = 0; ix < x; ix++)
        {
            for(int iy = 0; iy < y; iy++)
                {
                    for(int iz = 0; iz < z; iz++)
                        {
                            retMatrix[ix][iy][iz] = readNextVal<uint32_t>(in);
                        }
                }
        }
    return retMatrix;
}

#endif	/* _3DIO_HPP */

