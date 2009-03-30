/* 
 * File:   matrixtask.cpp
 * Author: uli
 * 
 * Created on 29. März 2009, 19:38
 */

#include <boost/type_traits/extent.hpp>

#include "../include/matrixtask.hpp"

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
 * \return The converted unsigned integer
 */
inline uint
readNextVal (std::istream& in)
{
    static string buffer; //Buffers the digits read from in
    static char c;
    buffer = "";

    while (true) //Break condition: return
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
                            return boost::lexical_cast<uint > (buffer);
                        }
                }
            //else: continue
        }
}

/**
 * Reads in a multi-dimensional array
 * Toplevel function, so no template needed (at least yet)
 * @\param x The x extent
 * @\param y The y extent
 * @\param z The z extent
 * @\param in The istream to read the data from
 */
inline Matrix3d
readMatrix3d (uint x, uint y, uint z, std::istream& in)
{
    Matrix3d retMatrix (boost::extents[x][y][z]);

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

MatrixTask::MatrixTask (std::istream& in)
{
    this->matrix = readMatrix (in);
}

MatrixTask::MatrixTask (string filename)
{
    ifstream in (filename.c_str ());
    this->matrix = readMatrix (in);
}

MatrixTask::MatrixTask(uint x, uint y, uint z)
{
    matrix(boost::extent[x][y][z]);
}

Matrix2d
MatrixTask::sumUpMatrix ()
{
    Matrix2d ret(boost::extent[xExt][yExt]);
    for (int x = 0; x < this->xExt; x++)
        {
            for (int y = 0; y < this->yExt; y++)
                {
                    ret[x][y] = 0;
                    for (int z = 0; z < this->zExt; z++)
                        {
                            ret[x][y] += matrix[x][y][z];
                        }
                }
        }
    return ret;
}

