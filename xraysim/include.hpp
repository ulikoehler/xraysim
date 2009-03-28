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

using namespace std;
using namespace boost;

//Typedefs
typedef boost::multi_array<uint32_t, 3> matrix3d;
typedef boost::multi_array<uint32_t, 2> matrix2d;

//Constant decs
#define FIELD_DELIM ',' //Character that separates 2 values in the data file

#endif	/* _INCLUDE_HPP */

