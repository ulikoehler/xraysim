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
    double x;
    double y;
};

/**
 * Calculates the coordinates of the middle of the image
 * \param alpha Alpha in radiants
 */
inline
struct Point calculateE(const float alpha, const float r)
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
struct Point calculateG(Point& e, const float re)
{
    Point p SSE;
    p.x = e.x + re * cos(alpha);
    p.y = e.x + re * sin(alpha);
    return p;
};

/**
 * \param a The lower left corner of the pixel
 * \param g The right delimiter of the image pixel to be mapped (see diagram in algorithms directory)
 * \param h The left delimiter of the image pixel to be mapped (see diagram in algorithms directory)
 * \param tana The tangens(!) of alpha. Note that alpha itself is not required
 */
inline
float calculatePixelEffect(const Point& a, const Point& g, const Point& h, const register double tana)
{
    /**
     * CPU Note: There are 16 FPU and 8-16 SSE registers so there should be
     *           no problem when declaring many register doubles
     *
     * Note: All these are x-coordinates
     */
    register double GAx; //Lower intersection point emitted by g
    register double GDx; //Upper intersection point emitted by g
    register double HAx; //Lower intersection point emitted by h
    register double HDx; //Upper intersection point emitted by h
    register double effect = 0;
    /**
     * Notes:
     * SAx is the lower intersection point; SDx the upper.
     * a is the lower left corner of the pixel, so a.y + 1 is the y coordinate of the upper left corner
     */
    GAx = tana * (g.y - a.y)  - (a.x - g.x);
    GDx = tana * (g.y - (a.y + 1.0))  - (a.x - g.x);
    HAx = tana * (h.y - a.y)  - (a.x - h.x);
    HDx = tana * (h.y - (a.y + 1.0))  - (a.x - h.x);

    //Test if the pixel is completely outside of the 'ray'
    //(if all 4 intersection point x coordinates are either all less or all greater than the appropriate coordinates)
    if(((GDx > (a.x + 1) && GAx > (a.x + 1)) || (GDx < (a.x) && GAx < (a.x + 1)))
            && ((HDx > (a.x + 1) && HAx > (a.x + 1)) || (HDx < (a.x) && HAx < (a.x + 1))))
        {
            return 0.0; //No effect on the pixels
        }
    //Check if SD.x is outside the CD edge; if yes, use a special effect calculation algorithm
    else if(GDx < a.x)
        {
            register double ae = 1 - (tana * (a.x - GDx)); //This is used in both branches
            //Check if SA.x is outside B.x -> We have to calculate a trapeze
            if(GAx > (a.x + 1.0))
                {
                    register double be;
                    be = 1 - (tana * (GAx - (a.x + 1)));
                    //Here a trapeze has been constructed using the secondary intersection points
                    //The trapeze height is the lower edge of the pixel (and thus equal to 1)
                    effect = (ae + be) / 2;
                }
            else
                {
                    /**
                     * We have to calculate the area of a triangle
                     * with vertices A, SA and the secondary intersection point
                     * A(Triangle) = (g * h) /2
                     * here g = distance A-SA; h = distance A-sec. int. point
                     * h has already been calculated and is saved in ae
                     */
                    effect =

                }
        }
    return effect;
}
#endif	/* _FPMATH_HPP */

