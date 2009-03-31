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

    inline uint
    getXExtent ()
    {
        return xExt;
    }

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
    //TODO Document

    class Matrix2dProxy
    {
    public:
        uint * operator[](const size_t& index); //TODO Document
        Matrix2dProxy (const size_t& xIndex, Matrix3d& inst); //TODO Document
    protected:
        size_t xIndex;
        Matrix3d* matrix;
    };
public:
    Matrix3d (const uint& x, const uint& y, const uint& z); //TODO Document
    ~Matrix3d ();
    Matrix2dProxy& operator[](const int& index); //TODO Document
    //TODO Document

    inline uint
    getXExtent ()
    {
        return xExt;
    }

    inline uint
    getYExtent ()
    {
        return yExt;
    }

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

