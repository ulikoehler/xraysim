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
    matrix = new Matrix3d (readMatrix (in));
}

MatrixTask::MatrixTask (std::string& filename)
{
    ifstream in (filename.c_str ());
    matrix = new Matrix3d (readMatrix (in));
}

MatrixTask::MatrixTask (const uint& x, const uint& y, const uint& z)
{
    matrix = new Matrix3d (x, y, z);
}

Matrix2d
MatrixTask::sumUpMatrix ()
{
    Matrix2d ret (xExt, yExt);
    for (int x = 0; x < xExt; x++)
        {
            for (int y = 0; y < yExt; y++)
                {
                    ret[x][y] = 0;
                    for (int z = 0; z < zExt; z++)
                        {
                            ret[x][y] = ret[x][y] + (*matrix)[x][y][z];
                        }
                }
        }
    return ret;
}
