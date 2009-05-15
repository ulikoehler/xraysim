#include "matrix.h"


/////////////
//Matrix 2d//
/////////////

Matrix::~Matrix ()
{
    delete array;
}

Matrix::Matrix (const uint x, const uint y)
{
    this->xExt = x;
    this->yExt = y;
    array = new uint[x * y];
}

uint*
Matrix::operator[](const size_t& index)
{
    return getArrayAt (index);
}

uint*
Matrix::getArrayAt (const uint& index)
{
    /**
     * Return an array beginning from the index the user selected
     * (Can be dereferenced again) so the syntax may be matrix2dInst[..][..]
     */
    return array + (index * yExt);
}

//TODO Test

uint
Matrix::getElementAt (const uint& x, const uint& y)
{
    //In fact this is equal to return getArrayAt(x)[y]; but here getArrayAt is inlined
    return array[x * xExt + y];
}

void
Matrix::setElementAt (const uint& x, const uint& y, const uint& val)
{
    array[x * xExt + y] = val;
}
