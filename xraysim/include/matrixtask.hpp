/* 
 * File:   matrixtask.hpp
 * Author: uli
 *
 * Created on 29. März 2009, 19:38
 */

#ifndef _MATRIXTASK_HPP
#define	_MATRIXTASK_HPP

#include "../include/3dio.hpp"

/**
 * A manager class to manage the matrix importing,
 */
class MatrixTask
{
public:
    /**
     * Constructs a new MatrixTask from an input stream
     * See data-spec.txt for a specification of the data format
     * \param in The input to read from
     */
    MatrixTask (std::istream& in);
    /**
     * Constructs a new MatrixTask from a given filename
     * See data-spec.txt for a specification of the data format
     * \param filename The name of an existing file to read the matrix from
     */
    MatrixTask (string filename);

    ///////////////////////
    //Getters and setters//
    ///////////////////////

    /**
     * Getter for the 3d matrix member variable
     * \return The matrix member
     */
    Matrix3d&
    getMatrix ()
    {
        return this->matrix;
    }
    /**
     * Sums up the z vectors of a given matrix
     * \param matrix The matrix to sum up from
     * \return A 2d matrix containing the summed data
     */
    Matrix2d sumUpMatrix ();
private:
    uint xExt, yExt, zExt; //Extents
    Matrix3d matrix; //The matrix

};

#endif	/* _MATRIXTASK_HPP */

