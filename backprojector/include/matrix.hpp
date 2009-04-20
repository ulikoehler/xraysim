/*
 * File:   matrix2d.hpp
 * Author: uli
 *
 * Created on 30. März 2009, 19:45
 */

#ifndef _MATRIX2D_HPP
#define	_MATRIX2D_HPP

#include "include.hpp"

//TODO Document

class Matrix2d
{
public:
    /**
     * Constructs a new Matrix2d object from given extents
     * \param x The X extent to use
     * \param y The Y extent to use
     */
    Matrix2d (const uint& x, const uint& y);
    /**
     * Reads a Matrix2d object from a stream
     * The stream must be uncompressed-
     * \param in The input stream to read the object from
     */
    Matrix2d(std::istream& in);

    /**
     * Constructs a Matrix2d object from a given filename
     * The filename is either asserted uncompressed or, if it ends to ".gz", Gzipped.
     * \param filename The filename of the file to read the data from
     */
    Matrix2d(std::string& filename);

    ~Matrix2d ();

    /**
     * Accesses a y value array (not copied) for the specified x value
     * \param index The x index to access (beginning from 0)
     * \return An unsigned integer pointer pointing to the first y value of the specified x
     * The pointer should be used as array again; if a y value greater than yExt-1 is used, it leads to undefined behaviour
     */
    uint* operator[](const size_t& index); //TODO Document

    /**
     * Accesses a y value array (not copied) for the specified x value
     * \param index The x index to access (beginning from 0)
     * \return An unsigned integer pointer pointing to the first y value of the specified x
     * The pointer should be used as array again; if a y value greater than yExt-1 is used, it leads to undefined behaviour
     */
    uint* getArrayAt(const uint& index);

    /**
     * Gets a specific value in the matrix
     * \param x The x index of the value (beginning from 0)
     * \param y The y index of the value (beginning from 0)
     * \return A copy of the value decscribed by x and y
     */
    uint getElementAt(const uint& x, const uint& y);
    
    /**
     * Sets a specific value in the matrix
     * \param x The x index of the value (beginning from 0)
     * \param y The y index of the value (beginning from 0)
     * \param val The value to set to
     */
    void setElementAt(const uint& x, const uint& y, const uint& val);
    /**
     * Serializes a matrix into an output stream
     * \param out The output stream to serialize to
     */
    void writeTo(std::ostream& out);
    
    #ifndef NO_CAIRO
    /**
     * Exports the matrix to a 2d graphics file
     * \param filename The filename of the PNG file to write to (is overwritten if it exists)
     * Requires Cairo
     */
    void writeToPNG(std::string filename);
    #endif
    /**
     * Serializes a matrix into an output stream
     * \param out The output stream to serialize to
     */
    friend std::ostream& operator<< (std::ostream& out, Matrix2d& matrix);
    /**
     *
     */
    friend std::istream& operator>> (std::istream& in, Matrix2d& matrix);
    /**
     * X extent getter
     * \return A copy of the x extent of this matrix instance
     */
    uint
    getXExtent ()
    {
        return xExt;
    }
    /**
     * Y extent getter
     * \return A copy of the y extent of this matrix instance
     */
    uint
    getYExtent ()
    {
        return yExt;
    }
private:
    void ReadFromPlainStream (std::istream& in);
    void ReadFromGzipStream (std::string& filename);
    uint xExt; //X Extent
    uint yExt; //Y Extent
    uint *array; //Data
};
//Overloaded IO operators
std::ostream& operator<< (std::ostream& out, Matrix2d& matrix);
std::istream& operator>> (std::istream& in, Matrix2d& matrix);

//TODO Document
class Matrix3d
{
    /**
     * A proxy class to enable expressions like
     * matrix3dInstance[x][y][z]
     *
     * Note:
     * matrix3dInstance[x][y] returns an array
     * 
     * Warning:
     * matrix3dInstance[x]
     * is not a valid number.
     */
    class Matrix2dProxy
    {
        friend class Matrix3d;
    public:
        /**
         * Operator to access the z values of a 3d matrix
         * \return An unsigned integer array containing the z values and
         *         with a length equal to the z extent of the matrix creating this instance
         */
        uint * operator[](const size_t& index);
    protected:
        Matrix2dProxy (const size_t& xIndex, Matrix3d& inst);
        size_t xIndex;
        Matrix3d* matrix;
    };
public:
    /**
     * Constructs a three-dimensional matrix with given extents
     * \param x The x extent
     * \param y The y extent
     * \param z The z extent
     */
    Matrix3d (const uint& x, const uint& y, const uint& z); //TODO Document
    ~Matrix3d ();
    /**
     * Accesses a 3d matrix for a given x index
     * \param index The x index to access
     * \return A proxy object to be used like an array again
     */
    Matrix2dProxy operator[](const int& index); //TODO Document

    /**
     * Adds up the z values of the matrix instance producing a 2d-matrix
     * \return A 2d matrix containing the z value sums
     */
    Matrix2d addUpZValues();

    /**
     * X extent getter
     * \return A copy of the x extent of this matrix instance
     */
    inline uint
    getXExtent ()
    {
        return xExt;
    }

    /**
     * Y extent getter
     * \return A copy of the y extent of this matrix instance
     */
    inline uint
    getYExtent ()
    {
        return yExt;
    }

    /**
     * Z extent getter
     * \return A copy of the z extent of this matrix instance
     */
    inline uint
    getZExtent ()
    {
        return zExt;
    }
protected:
    uint xExt; //X Extent
    uint yExt; //Y Extent
    uint zExt; //Z Extent
    uint *array; //Data
};

/**
 * Matrix comparison operators
 */
bool operator== (Matrix3d& matrix, Matrix3d& otherMatrix);
bool operator== (Matrix2d& matrix, Matrix2d& otherMatrix);

#endif	/* _MATRIX2D_HPP */

