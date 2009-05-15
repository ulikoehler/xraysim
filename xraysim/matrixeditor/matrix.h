#ifndef MATRIX_H
#define MATRIX_H
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

class Matrix
{
public:
    /**
     * Constructs a new Matrix object from given extents
     * \param x The X extent to use
     * \param y The Y extent to use
     */
    Matrix (const uint x, const uint y);

    ~Matrix ();

    /**
     * Accesses a y value array (not copied) for the specified x value
     * \param index The x index to access (beginning from 0)
     * \return An unsigned integer pointer pointing to the first y value of the specified x
     * The pointer should be used as array again; if a y value greater than yExt-1 is used, it leads to undefined behaviour
     */
    uint* operator[](const size_t& index); //TODO Document

    /**
     * Accesses a y value array (not copied) for the specified x value
     * \param index The x index to access (beginning from 0)
     * \return An unsigned integer pointer pointing to the first y value of the specified x
     * The pointer should be used as array again; if a y value greater than yExt-1 is used, it leads to undefined behaviour
     */
    uint* getArrayAt(const uint& index);

    /**
     * Gets a specific value in the matrix
     * \param x The x index of the value (beginning from 0)
     * \param y The y index of the value (beginning from 0)
     * \return A copy of the value decscribed by x and y
     */
    uint getElementAt(const uint& x, const uint& y);

    /**
     * Sets a specific value in the matrix
     * \param x The x index of the value (beginning from 0)
     * \param y The y index of the value (beginning from 0)
     * \param val The value to set to
     */
    void setElementAt(const uint& x, const uint& y, const uint& val);

    /**
     * X extent getter
     * \return A copy of the x extent of this matrix instance
     */
    uint
    getXExtent ()
    {
        return xExt;
    }
    /**
     * Y extent getter
     * \return A copy of the y extent of this matrix instance
     */
    uint
    getYExtent ()
    {
        return yExt;
    }
private:
    uint xExt; //X Extent
    uint yExt; //Y Extent
    uint *array; //Data
};

#endif // MATRIX_H
