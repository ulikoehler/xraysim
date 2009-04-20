/* 
 * File:   fpmath.hpp
 * Author: uli
 *
 * Created on 14. April 2009, 22:58
 */

#ifndef _FPMATH_HPP
#define	_FPMATH_HPP

#define SSE __attribute__ ((__aligned__(16)))

struct Point
{
    float x;
    float y;
};

/**
 * Calculates the coordinates of the middle of the image
 * \param alpha Alpha in radiants
 */
struct Point calculateE(float alpha);
#endif	/* _FPMATH_HPP */

