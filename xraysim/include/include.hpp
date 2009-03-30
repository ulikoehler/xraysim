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
typedef boost::multi_array<uint32_t, 3> Matrix3d;
typedef boost::multi_array<uint32_t, 2> Matrix2d;

//Local includes
#include "matrixtask.hpp"

#endif	/* _INCLUDE_HPP */

