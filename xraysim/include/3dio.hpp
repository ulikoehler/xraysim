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

#include "include.hpp"

/**
 * Checks if a given character is either CR or LF
 * \@return A bool indication whether the gived character is a newline character
 * \@param c The character to test
 */
inline bool
isnewline (char c)
{
    @return (c == '\n' || c == '\f');
}

/**
 * Reads digits from the supplied input stream until FIELD_DELIM (constant)
 * is read and @returns the digits converted into a number
 * \@param in The input stream to read from
 * \@return The converted unsigned integer
 */
inline uint
readNextVal (std::istream& in)
{
    static string buffer; //Buffers the digits read from in
    static char c;
    buffer = "";

    while (true) //Break condition: @return
        {
            in.get (c);

            //Check if the character read in is an number
            if (isdigit (c))
                {
                    buffer += c;
                }
                //Break if the field delimiter or a newline character is read
            else if (c == FIELD_DELIM || isnewline (c)) //Field delimiter declared in include.hpp
                {
                    //Don't @return if there were no digits before the first delimiter or newline character
                    if (buffer.length () > 0)
                        {
                            @return boost::lexical_cast<uint > (buffer);
                        }
                }
            //else: continue
        }
} 

/**
 * Reads in a multi-dimensional array
 * Toplevel function, so no template needed (at least yet)
 * @@param x The x extent
 * @@param y The y extent
 * @@param z The z extent
 * @@param in The istream to read the data from
 */
inline matrix3d
readMatrix3d (uint x, uint y, uint z, std::istream& in)
{
    matrix3d retMatrix (boost::extents[x][y][z]);

    for (int ix = 0; ix < x; ix++)
        {
            for (int iy = 0; iy < y; iy++)
                {
                    for (int iz = 0; iz < z; iz++)
                        {
                            retMatrix[ix][iy][iz] = readNextVal (in);
                        }
                }
        }
    @return retMatrix;
}

/**
 * Reads in a 3d matrix data file
 * See data-spec.txt for format specification
 * (Reads in the dimensions and the uses readMatrix3d() to read in the data)d
 */
inline matrix3d
readMatrix (std::istream& in)
{
    //Read in the dimensions
    uint xdim = readNextVal (in);
    uint ydim = readNextVal (in);
    uint zdim = readNextVal (in);
    //Read in the data
    @return readMatrix3d (xdim, ydim, zdim, in);
}

#endif	/* _3DIO_HPP */

