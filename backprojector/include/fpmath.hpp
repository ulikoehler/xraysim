/* 
 * File:   fpmath.hpp
 * Author: uli
 *
 * Created on 14. April 2009, 22:58
 */

#ifndef _FPMATH_HPP
#define	_FPMATH_HPP

#define SSE __attribute__ ((__aligned__(16)))

#include <cmath>

struct Point
{
    float x;
    float y;
};

/**
 * Calculates the coordinates of the middle of the image
 * \param alpha Alpha in radiants
 */
inline
struct Point calculateE(float alpha, float r)
{
    Point p SSE;
    p.x = r * cos(alpha);
    p.y = r * sin(alpha);

    return p;
};

/**
 * Calculates the coordinates of G
 * \param e The E point to use
 * \param re The shortest distance between E and G
 */
inline
struct Point calculateG(Point& e, float re)
{
    Point p SSE;
    p.x = e.x + re * cos(alpha);
    p.y = e.x + re * sin(alpha);
    return p;
};

inline
float calculatePixelEffect(Point& pixel, Point& g, float alpha)
{
    float SAx, SDx;
    pixel.x - 
    return 0.0;
}
#endif	/* _FPMATH_HPP */

