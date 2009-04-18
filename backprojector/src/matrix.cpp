/* 
 * File:   matrix2d.cpp
 * Author: uli
 * 
 * Created on 30. März 2009, 19:45
 */

#include "../include/matrix.hpp"
#include "../include/io_utils.hpp"
#include <climits>

#include <zlib.h>

#ifndef NO_CAIRO
#include <cairo/cairo.h>
#endif

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

///Gzip code
#define CHUNKSIZE 16384


int Matrix2d::ReadFromGz (std::istream& in)
{
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = inflateInit (&strm);
    if (ret != Z_OK)
        {
            cerr << "Error in GZ decompression";
        }

    /* decompress until deflate stream ends or end of file */
    do
        {

            strm.avail_in = in.read();
            if (!in.good())
                {
                    (void) inflateEnd (&strm);
                    return Z_ERRNO;
                }
            if (strm.avail_in == 0) break;
            strm.next_in = in;

            /* run inflate() on input until output buffer not full */
            do
                {
                    strm.avail_out = CHUNK;
                    strm.next_out = out;
                    ret = inflate (&strm, Z_NO_FLUSH);
                    assert (ret != Z_STREAM_ERROR); /* state not clobbered */
                    switch (ret)
                        {
                        case Z_NEED_DICT:
                            ret = Z_DATA_ERROR; /* and fall through */
                        case Z_DATA_ERROR:
                        case Z_MEM_ERROR:
                            (void) inflateEnd (&strm);
                            return ret;
                        }
                    have = CHUNK - strm.avail_out;
                    if (fwrite (out, 1, have, dest) != have || ferror (dest))
                        {
                            (void) inflateEnd (&strm);
                            return Z_ERRNO;
                        }
                }
            while (strm.avail_out == 0);

            /* done when inflate() says it's done */
        }
    while (ret != Z_STREAM_END);

    /* clean up and return */
    (void) inflateEnd (&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;


}

void
Matrix2d::ReadFromPlainStream ()
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

Matrix2d::Matrix2d (std::string& filename)
{
    if (filename.find (".gz") == (filename.length () - 3)) //string.length() - ".gz".length()
        {
            ReadFromGzStream ();
        }
    else
        {
            ReadFromPlainStream ();
        }

}

Matrix2d::Matrix2d (std::istream& in) {
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


