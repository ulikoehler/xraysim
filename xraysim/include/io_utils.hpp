/* 
 * File:   io_utils.hpp
 * Author: uli
 *
 * Some IO utility functions
 * To be includes from test files and matrixtask.cpp
 * Don't include in include.hpp
 *
 * Created on 30. März 2009, 14:25
 */

#ifndef _IO_UTILS_HPP
#define	_IO_UTILS_HPP

/**
 * Checks if a given character is either CR or LF
 * \return A bool indication whether the gived character is a newline character
 * \param c The character to test
 */
inline bool
isnewline (char c)
{
    return (c == '\n' || c == '\f');
}

/**
 * Reads the next value from the supplied input stream until FIELD_DELIM (constant)
 * is read and returns the digits casted into a number
 * \param in The input stream to read from
 * \param val The variable to save the result in
 * \return A status code; 0 means success
 */
inline uint
readNextVal (std::istream& in, uint& val)
{
    string buffer; //Buffers the digits read from in
    char c;
    buffer = "";

    while (in.good()) //Break condition: return
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
                    //Don't* \return if there were no digits before the first delimiter or newline character
                    if (buffer.length () > 0)
                        {
                            val = atoi (buffer.c_str());
			    return 0;
                        }
                }
            //else: continue
        }
	return 1;
}

inline uint readNextVal(std::istream& in)
{
	uint val;
	readNextVal(in, val);
	return val;
}

/**
 * Reads in a multi-dimensional array
 * @\param x The x extent
 * @\param y The y extent
 * @\param z The z extent
 * @\param in The istream to read the data from
 */
inline Matrix3d
readMatrix3d (uint x, uint y, uint z, std::istream& in)
{
    Matrix3d retMatrix (x,y,z);

    for (int ix = 0; ix < x; ix++)
        {
            for (int iy = 0; iy < y; iy++)
                {
                    for (int iz = 0; iz < z; iz++)
                        {
			    uint val;
			    //Store the value in the matrix if the value has been read successfully
			    if(readNextVal(in, val)) {retMatrix[ix][iy][iz] = val;}
                        }
                }
        }
    return retMatrix;
}

/**
 * Reads in a 3d matrix data file
 * See data-spec.txt for format specification
 * (Reads in the extents and the uses readMatrix3d() to read in the data)
 * \return The matrix read in
 */
inline Matrix3d
readMatrix (std::istream& in)
{
    //Read in the dimensions
    uint xdim = readNextVal (in);
    uint ydim = readNextVal (in);
    uint zdim = readNextVal (in);
    //Read in the data
    return readMatrix3d (xdim, ydim, zdim, in);
}

#endif	/* _IO_UTILS_HPP */

