/* 
 * File:   matrix2d.hpp
 * Author: uli
 *
 * Created on 30. März 2009, 19:45
 */

#ifndef _MATRIX2D_HPP
#define	_MATRIX2D_HPP

template <class val_type = uint>
class Matrix2d
{
public:
    //TODO Document
    Matrix2d ();
    Matrix2d (const Matrix2d& orig);
    Matrix2d(uint x, uint y);
    ~Matrix2d();
    val_type operator[](uint index);
private:
    uint xEx; //X Extent
    uint yEx; //Y Extent
    val_type *array;

};

#endif	/* _MATRIX2D_HPP */

