/* 
 * File:   matrixtask.cpp
 * Author: uli
 * 
 * Created on 29. März 2009, 19:38
 */

#include "../include/include.hpp"
#include "../include/io_utils.hpp"


MatrixTask::MatrixTask (std::istream& in)
{
    this->matrix = readMatrix (in);
}

MatrixTask::MatrixTask (string filename)
{
    ifstream in (filename.c_str ());
    this->matrix = readMatrix (in);
}

MatrixTask::MatrixTask(uint x, uint y, uint z)
{
    //this->matrix = Matrix3d(boost::extents[x][y][z]);
}

Matrix2d
MatrixTask::sumUpMatrix ()
{
    Matrix2d ret(boost::extents[2][3]);
    for (int x = 0; x < this->xExt; x++)
        {
            for (int y = 0; y < this->yExt; y++)
                {
                    ret[x][y] = 0;
                    for (int z = 0; z < this->zExt; z++)
                        {
                            ret[x][y] += matrix[x][y][z];
                        }
                }
        }
    return ret;
}

