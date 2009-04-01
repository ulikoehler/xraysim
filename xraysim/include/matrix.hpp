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
//TODO Make template

class Matrix2d
{
public:
    Matrix2d (const uint& x, const uint& y); //TODO Document
    ~Matrix2d ();

    void setAt (const uint& val, const size_t& x, const size_t& y);

    uint * operator[](const size_t& index); //TODO Document

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
private:
    uint xExt; //X Extent
    uint yExt; //Y Extent
    uint *array; //Data
};

//TODO Document
//TODO Make template

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

