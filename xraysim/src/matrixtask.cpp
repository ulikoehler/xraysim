/* 
 * File:   matrixtask.cpp
 * Author: uli
 * 
 * Created on 29. März 2009, 19:38
 */

#include "../include/matrixtask.hpp"
#include "../include/include.hpp"
#include "../include/io_utils.hpp"

MatrixTask::MatrixTask (std::istream& in)
{
    this->matrix = new Matrix3d (readMatrix (in));
}

MatrixTask::MatrixTask (std::string& filename)
{
    ifstream in (filename.c_str ());
    this->matrix = new Matrix3d (readMatrix (in));
}

MatrixTask::MatrixTask (uint& x, uint& y, uint& z)
{
    this->matrix = new Matrix3d (x, y, z);
}

Matrix2d
MatrixTask::sumUpMatrix ()
{
    Matrix2d ret (this->xExt, this->yExt);
    for (int x = 0; x < this->xExt; x++)
        {
            for (int y = 0; y < yExt; y++)
                {
                    ret[x][y] = 0;
                    for (int z = 0; z < zExt; z++)
                        {
                            ret[x][y] += matrix[x][y][z];
                        }
                }
        }
    return ret;
}
