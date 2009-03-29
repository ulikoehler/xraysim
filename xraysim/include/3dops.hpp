/* 
 * File:   3dops.hpp
 * Author: uli
 *
 * Created on 27. März 2009, 22:02
 */

#ifndef _3DOPS_HPP
#define	_3DOPS_HPP

#include "include.hpp"

/**
 * Sums up the z vectors of a given matrix
 * \param matrix The matrix to sum up from
 * \return A 2d matrix containing the summed data
 */
inline Matrix2d sumUpMatrix(Matrix3d matrix)
{
    //For each vector in the map //TODO
}

/**
 * Helper to get the dimensions of a three-dimensional matrix
 * \param matrix The matrix to get the dimensions from
 * \return A 3d vector of the dimensions
 */
inline Vector3d matrixExtents(Matrix3d matrix)
{
    const Matrix3d::size_type* shape = matrix.shape();
    Vector3d ret(shape[0], shape[1], shape[2]);
    return ret;
}

#endif	/* _3DOPS_HPP */

