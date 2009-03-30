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

Matrix2d::Matrix2d(uint x, uint y)
{
    this->xExt = x;
    this->yExt = y;
    array = new uint[x * y];
}

uint*
Matrix2d::operator[](const int& index)
{
    /**
     * Return an array beginning from the index the user selected
     * (Can be dereferenced again) so the syntax may be matrix2dInst[..][..]
     */
    return array + (index * this->yExt);
}