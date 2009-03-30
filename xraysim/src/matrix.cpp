/* 
 * File:   matrix2d.cpp
 * Author: uli
 * 
 * Created on 30. März 2009, 19:45
 */

#include "../include/matrix.hpp"

Matrix2d::~Matrix2d ()
{
    delete array;
}

Matrix2d::Matrix2d (uint x, uint y)
{
    xEx = x;
    yEx = y;
    array = new val_type[x * y];
}

~Matrix2d ()
{
    delete array;
}

val_type*
Matrix2d::operator[]()
{
    return array + (x * yExt);
}