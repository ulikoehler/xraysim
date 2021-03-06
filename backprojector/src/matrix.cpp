/* 
 * File:   matrix2d.cpp
 * Author: uli
 * 
 * Created on 30. März 2009, 19:45
 */

#include "../include/matrix.hpp"
#include <climits>

#ifndef NO_CAIRO
#endif

/////////////////////
//General Utilities//
/////////////////////
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

#ifndef NOZLIB
#include <zlib.h>

//TODO Fix doc: reads from a gz file
/**
 * Reads the next value from the supplied input stream until FIELD_DELIM (constant)
 * is read and returns the digits casted into a number
 * \param in The input stream to read from
 * \param val The variable to save the result in
 * \return A status code; 0 means success
 */
inline uint
readNextVal (gzFile file)
{
    string buffer; //Buffers the digits read from in
    char c;
    buffer = "";

    while (!gzeof(file)) //Break condition: return
        {
            c = gzgetc(file);
            
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
                            return atoi (buffer.c_str());
                        }
                }
            //else: continue
        }
	return 0;
}

#endif //NOZLIB

/**
 * Reads the next value from the supplied input stream until FIELD_DELIM (constant)
 * is read and returns the digits casted into a number
 * \param in The input stream to read from
 * \param val The variable to save the result in
 * \return A status code; 0 means success
 */
inline uint
readNextVal (std::istream& in)
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
                            return atoi (buffer.c_str());
                        }
                }
            //else: continue
        }
	return 0;
}


/////////////
//Matrix 2d//
/////////////

Matrix2d::~Matrix2d ()
{
    delete array;
}

void
Matrix2d::writeTo (std::ostream& out)
{
    //Print the extents (first line)
    out << xExt << ',' << yExt << '\n';
    //Print the data
    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    out << this->getElementAt (ix, iy);
                    if ((yExt - iy) > 1)
                        {
                            out << ',';
                        }
                }
            if ((xExt - ix) > 1)
                {
                    out << '\n';
                }
        }
}

void
Matrix2d::ReadFromPlainStream (std::istream& in)
{
    //Read in the first line (the coordinates)
    int x = readNextVal (in);
    cout << "Xdim: " << x << endl;
    int y = readNextVal (in);
    cout << "Ydim: " << y << endl;
    //Matrix2d(x, y);
    this->xExt = x;
    this->yExt = y;
    //Check if there already is an array to be deleted
    if (array != NULL)
        {
            delete array;
        }
    array = new uint[x * y];

    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    setElementAt (ix, iy, readNextVal (in));
                }
        }
}

#ifndef NOZLIB
void
Matrix2d::ReadFromGzipStream (std::string& filename)
{
    gzFile file = gzopen(filename.c_str(), "rb");
    //Read in the first line (the coordinates)
    int x = readNextVal (file);
    cout << "Xdim: " << x << endl;
    int y = readNextVal (file);
    cout << "Ydim: " << y << endl;
    //Matrix2d(x, y);
    this->xExt = x;
    this->yExt = y;
    //Check if there already is an array to be deleted
    if (array != NULL)
        {
            delete array;
        }
    array = new uint[x * y];

    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    setElementAt (ix, iy, readNextVal (file));
                }
        }
    //Close the input file
    gzclose(file);
}
#endif //NOZLIB

Matrix2d::Matrix2d (std::string& filename)
{
    if (filename.find (".gz") == (filename.length () - 3)) //string.length() - ".gz".length()
        {
            ReadFromGzipStream (filename);
        }
    else
        {
            ifstream f(filename.c_str());
            ReadFromPlainStream (f);
            f.close();
        }

}

Matrix2d::Matrix2d (std::istream& in)
{
    ReadFromPlainStream(in);
}

Matrix2d::Matrix2d (const uint& x, const uint& y)
{
    this->xExt = x;
    this->yExt = y;
    array = new uint[x * y];
}

uint*
Matrix2d::operator[](const size_t& index)
{
    return getArrayAt (index);
}

uint*
Matrix2d::getArrayAt (const uint& index)
{
    /**
     * Return an array beginning from the index the user selected
     * (Can be dereferenced again) so the syntax may be matrix2dInst[..][..]
     */
    return array + (index * yExt);
}

//TODO Test

uint
Matrix2d::getElementAt (const uint& x, const uint& y)
{
    //In fact this is equal to return getArrayAt(x)[y]; but here getArrayAt is inlined
    return array[x * xExt + y];
}

void
Matrix2d::setElementAt (const uint& x, const uint& y, const uint& val)
{
    array[x * xExt + y] = val;
}

#ifndef NO_CAIRO
#include <cairo/cairo.h>

void
Matrix2d::writeToPNG (std::string filename)
{
    //TODO Comment
    cairo_surface_t* s = cairo_image_surface_create (CAIRO_FORMAT_RGB24, xExt, yExt);
    cairo_t* c = cairo_create (s);

    cairo_set_source_rgb (c, 1, 1, 1);
    cairo_set_operator (c, CAIRO_OPERATOR_SOURCE);
    cairo_paint (c);
    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    double val = (double) (UINT_MAX - getElementAt (ix, iy)) / UINT_MAX; //std::numeric_limits<uint>::max();
                    cairo_set_source_rgb (c, val, val, val);
                    cairo_rectangle (c, ix, iy, 1, 1);
                    cairo_stroke (c);
                }
        }
    cairo_surface_write_to_png (s, filename.c_str ());
}
#endif

//TODO Test
//Overloaded IO operators
std::ostream& operator<< (std::ostream& out, Matrix2d& matrix)
{
    matrix.writeTo(out);
    return out;
}

std::istream& operator>> (std::istream& in, Matrix2d& matrix)
{
    matrix.ReadFromPlainStream(in);
    return in;
}

/////////////
//Matrix 3d//
/////////////

Matrix3d::Matrix3d (const uint& x, const uint& y, const uint& z)
{
    this->xExt = x;
    this->yExt = y;
    this->zExt = z;
    array = new uint[x * y * z];
}

Matrix3d::Matrix2dProxy Matrix3d::operator[](const int& index)
{
    return Matrix3d::Matrix2dProxy (index, *this);
}

bool operator== (Matrix3d& matrix, Matrix3d& otherMatrix)
{
    //Check the dimensions
    if (matrix.getXExtent () != otherMatrix.getXExtent ())
        {
            return false;
        }
    if (matrix.getYExtent () != otherMatrix.getYExtent ())
        {
            return false;
        }
    if (matrix.getZExtent () != otherMatrix.getZExtent ())
        {
            return false;
        }
    //Check the elements
    for (int ix = 0; ix < matrix.getXExtent (); ix++)
        {
            for (int iy = 0; iy < matrix.getYExtent (); iy++)
                {
                    for (int iz = 0; iz < matrix.getZExtent (); iz++)
                        {
                            if (matrix[ix][iy][iz] != otherMatrix[ix][iy][iz])
                                {
                                    return false;
                                }
                        }
                }
        }
}

bool operator== (Matrix2d& matrix, Matrix2d& otherMatrix)
{
    //Check the dimensions
    if (matrix.getXExtent () != otherMatrix.getXExtent ())
        {
            return false;
        }
    if (matrix.getYExtent () != otherMatrix.getYExtent ())
        {
            return false;
        }
    //Check the elements
    for (int ix = 0; ix < matrix.getXExtent (); ix++)
        {
            for (int iy = 0; iy < matrix.getYExtent (); iy++)
                {
                    if (matrix[ix][iy] != otherMatrix[ix][iy])
                        {
                            return false;
                        }
                }
        }
    return true;
}

Matrix2d addUpZValues ();

Matrix3d::~Matrix3d ()
{
    delete [] array;
}

/**
 * Matrix2dProxy
 */

Matrix3d::Matrix2dProxy::Matrix2dProxy (const size_t& xIndex, Matrix3d& matrixInst)
{
    this->xIndex = xIndex;
    this->matrix = &matrixInst;
}

uint* Matrix3d::Matrix2dProxy::operator[](const size_t& yIndex)
{
    return matrix->array + ((xIndex + yIndex * matrix->xExt) * matrix->zExt);
}


