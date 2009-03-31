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
    Matrix2d(const uint& x, const uint& y); //TODO Document
    ~Matrix2d();

    void setAt(const uint& val, const size_t& x, const size_t& y);
    
    uint* operator[](const size_t& index); //TODO Document
private:
    uint xExt; //X Extent
    uint yExt; //Y Extent
    uint *array; //Data
};

//TODO Document
class Matrix3d
{
    //TODO Document
    class Matrix2dProxy
    {
    protected:
        Matrix2dProxy(const uint& index); //TODO Document
        uint* operator[](const size_t& index); //TODO Document
        size_t index;
    };
public:
    Matrix3d(const uint& x, const uint& y, const uint& z); //TODO Document
    ~Matrix3d();
    matrix2dProxy operator[](const int& index); //TODO Document
private:
    uint xExt; //X Extent
    uint yExt; //Y Extent
    uint zExt; //Z Extent
    uint *array; //Data
};

#endif	/* _MATRIX2D_HPP */

