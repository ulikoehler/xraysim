/* 
 * File:   matrix2d.cpp
 * Author: uli
 * 
 * Created on 30. März 2009, 19:45
 */

#include "../include/matrix.hpp"
#include "../include/io_utils.hpp"

/////////////
//Matrix 2d//
/////////////

Matrix2d::~Matrix2d ()
{
    delete array;
}

void Matrix2d::writeTo(std::ostream& out)
{
	//Print the extents (first line)
	out << xExt << ',' << yExt << '\n';
	//Print the data
	for(int ix = 0; ix < xExt; ix++)
	{
		for(int iy = 0; iy < yExt; iy++)
		{
			out << this->getElementAt(ix,iy);
			if((yExt - iy) > 1) {out << ',';}
		}
		if((xExt - ix) > 1) {out << '\n';}
	}
}

Matrix2d::Matrix2d(std::istream& in)
{
	//Read in the first line (the coordinates)
	int x = readNextVal(in);
	cout << "Xdim: " << x << endl;
	int y = readNextVal(in);
	cout << "Ydim: " << y << endl;
	//Matrix2d(x, y);
	this->xExt = x;
	this->yExt = y;
	array = new uint[x * y];
		
	for(int ix = 0; ix < xExt; ix++)
	{
		for(int iy = 0; iy < yExt; iy++)
		{
			this->setElementAt(ix, iy, readNextVal(in));
		}
	}
}

Matrix2d::Matrix2d (const uint& x, const uint& y)
{
    this->xExt = x;
    this->yExt = y;
    array = new uint[x * y];
}

uint*
Matrix2d::operator[](const size_t& index)
{
	return getArrayAt(index);
}

uint* Matrix2d::getArrayAt(const uint& index)
{
    /**
     * Return an array beginning from the index the user selected
     * (Can be dereferenced again) so the syntax may be matrix2dInst[..][..]
     */
    return array + (index * yExt);
}

//TODO Test
uint Matrix2d::getElementAt(const uint& x, const uint& y)
{
	return getArrayAt(x)[y];
}

void Matrix2d::setElementAt(const uint& x, const uint& y, const uint& val)
{
	array[x * xExt +y] = val;
}

/////////////
//Matrix 3d//
/////////////

Matrix3d::Matrix3d (const uint& x, const uint& y, const uint& z)
{
    this->xExt = x;
    this->yExt = y;
    this->zExt = z;
    array = new uint[x * y * z];
}


Matrix3d::Matrix2dProxy Matrix3d::operator[](const int& index)
{
    return Matrix3d::Matrix2dProxy(index, *this);
}

bool operator== (Matrix3d& matrix, Matrix3d& otherMatrix)
{
    //Check the dimensions
    if (matrix.getXExtent () != otherMatrix.getXExtent ())
        {
            return false;
        }
    if (matrix.getYExtent () != otherMatrix.getYExtent ())
        {
            return false;
        }
    if (matrix.getZExtent () != otherMatrix.getZExtent ())
        {
            return false;
        }
    //Check the elements
    for (int ix = 0; ix < matrix.getXExtent (); ix++)
        {
            for (int iy = 0; iy < matrix.getYExtent (); iy++)
                {
                    for (int iz = 0; iz < matrix.getZExtent (); iz++)
                        {
                            if (matrix[ix][iy][iz] != otherMatrix[ix][iy][iz])
                                {
                                    return false;
                                }
                        }
                }
        }
}

bool operator== (Matrix2d& matrix, Matrix2d& otherMatrix)
{
    //Check the dimensions
    if (matrix.getXExtent () != otherMatrix.getXExtent ())
        {
            return false;
        }
    if (matrix.getYExtent () != otherMatrix.getYExtent ())
        {
            return false;
        }
    //Check the elements
    for (int ix = 0; ix < matrix.getXExtent (); ix++)
        {
            for (int iy = 0; iy < matrix.getYExtent (); iy++)
                {
                    if (matrix[ix][iy] != otherMatrix[ix][iy])
                        {
                            return false;
                        }
                }
        }
    return true;
}

Matrix2d addUpZValues();

Matrix3d::~Matrix3d ()
{
    delete [] array;
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


