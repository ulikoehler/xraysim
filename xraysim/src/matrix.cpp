/* 
 * File:   matrix2d.cpp
 * Author: uli
 * 
 * Created on 30. März 2009, 19:45
 */

#include "../include/matrix.hpp"

/////////////
//Matrix 2d//
/////////////

Matrix2d::~Matrix2d ()
{
    delete array;
}

Matrix2d::Matrix2d (const uint& x, const uint& y)
{
    this->xExt = x;
    this->yExt = y;
    array = new uint[x * y];
}

void
setAt (const uint& val, const size_t& x, const size_t& y) {
 }

uint*
Matrix2d::operator[](const size_t& index)
{
    /**
     * Return an array beginning from the index the user selected
     * (Can be dereferenced again) so the syntax may be matrix2dInst[..][..]
     */
    return array + (index * this->yExt);
}

/////////////
//Matrix 3d//
/////////////
//TODO implement if needed (check Boost::multi_array performance)

Matrix3d::Matrix3d (const uint& x, const uint& y, const uint& z)
{
    this->xExt = x;
    this->yExt = y;
    this->zExt = z;
    array = new uint (x * y * z);
}

Matrix3d::~Matrix3d ()
{
    delete array;
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


