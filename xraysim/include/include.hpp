/* 
 * File:   include.hpp
 * Author: uli
 *
 * Created on 27. März 2009, 22:05
 */

#ifndef _INCLUDE_HPP
#define	_INCLUDE_HPP

#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/multi_array.hpp>

//Local includes
#include "matrixtask.hpp"

using namespace std;
using namespace boost;

//Typedefs
typedef boost::multi_array<uint32_t, 3> Matrix3d;
typedef boost::multi_array<uint32_t, 2> Matrix2d;

//Constant decs
#define FIELD_DELIM ',' //Character that separates 2 values in the data file

#endif	/* _INCLUDE_HPP */

