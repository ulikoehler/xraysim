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
    Matrix2d ();
    Matrix2d(const uint& x, const uint& y); //TODO Document
    ~Matrix2d();
    uint* operator[](const int& index); //TODO Document
private:
    uint xExt; //X Extent
    uint yExt; //Y Extent
    uint *array; //Data
};

#endif	/* _MATRIX2D_HPP */

