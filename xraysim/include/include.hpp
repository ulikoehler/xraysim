/* 
 * File:   include.hpp
 * Author: uli
 *
 * Created on 27. März 2009, 22:05
 */

#ifndef _INCLUDE_HPP
#define	_INCLUDE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/multi_array.hpp>

using namespace std;
using namespace boost;

//Constant decs
#define FIELD_DELIM ',' //Character that separates 2 values in the data file

//Typedefs
typedef boost::multi_array<uint32_t, 3> Matrix3d; //TODO: Implement as class
//typedef std::vector<std::vector<uint32_t> > Matrix2d;

//TODO Document
template <class val_type>
class Matrix2d
{
public:
    uint xEx; //X Extent
    uint yEx; //Y Extent
    val_type *array;
    //TODO Document
    Matrix2d(uint x, uint y)
    {
        xEx = x;
        yEx = y;
        array = new val_type[x * y];
    }
    ~Matrix2d()
    {
        delete array;
    }
    operator[]()
    {
        return x
    }
};

//Local includes
#include "matrixtask.hpp"

#endif	/* _INCLUDE_HPP */

