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
 * Describes precalculated intersection point prototypes:
 * The x coordinate of a left vertice of the pixel has to be substracted to get relative coordinates
 */
struct IntersectionPointPrototypes
{
    double GAxProto; //Lower horizontal intersection point emitted by g
    double GDxProto; //Upper horizontal intersection point emitted by g
    double HAxProto; //Lower horizontal intersection point emitted by h
    double HDxProto; //Upper horizontal intersection point emitted by h
};

/**
 * Calculates the coordinates of the middle of the image
 * \param alpha Alpha in radiants
 */
inline
struct Point
calculateE (const float alpha, const float r)
{
    Point p SSE;
    p.x = r * cos (alpha);
    p.y = r * sin (alpha);

    return p;
};

/**
 * Calculates the coordinates of G
 * \param e The E point to use
 * \param re The shortest distance between E and G
 */
inline
struct Point
calculateG (Point& e, const float re)
{
    Point p SSE;
    p.x = e.x + re * cos (alpha);
    p.y = e.x + re * sin (alpha);
    return p;
};

/**
 * The x coordinate of a left vertice of the pixel has to be substracted to get relative coordinates
 * \param tana The tangens of alpha
 */
inline struct IntersectionPointPrototypes
computeIntersectionPointCoordinates (const Point& g, const Point&a, const double tana)
{
    struct IntersectionPointPrototypes ip;
    ip.GAxProto = tana * (g.y - a.y);
    ip.GDxProto = tana * (g.y - (a.y + 1.0));
    ip.HAxProto = tana * (h.y - a.y);
    ip.HDxProto = tana * (h.y - (a.y + 1.0));
    return ip;
}

/**
 * \param a The lower left corner of the pixel
 * \param g The right delimiter of the image pixel to be mapped (see diagram in algorithms directory)
 * \param h The left delimiter of the image pixel to be mapped (see diagram in algorithms directory)
 * \param tana The tangens(!) of alpha. Note that alpha itself is not required
 */
inline
float
computePixelEffect (const Point& a, const IntersectionPointPrototypes& ip, const double tana)
{
    /**
     * CPU Note: There are 16 FPU and 8-16 SSE registers so there should be
     *           no problem when declaring many register doubles
     *
     * Note: All these are x-coordinates
     */

    register float effect = 0;

    //Distances A-point
    register double GAx = ip.GAxProto - a.x; //Lower intersection point emitted by g
    register double GDx = ip.GDxProto - a.x; //Upper intersection point emitted by g
    register double HAx = ip.HAxProto - a.x; //Lower intersection point emitted by h
    register double HDx = ip.HDxProto - a.x; //Upper intersection point emitted by h
    register double effect = 0;

    //Macros to check where the points are (in fact only on which side or in the pixel square)
    #define ISHDRIGHTOUTSIDE (HDx > (a.x + 1))
    #define ISHARIGHTOUTSIDE (HAx > (a.x + 1))
        #define ISHRIGHTOUTSIDE (ISHDRIGHTOUTSIDE && ISHARIGHTOUTSIDE)
    #define ISGDRIGHTOUTSIDE (HDx > (a.x + 1))
    #define ISGARIGHTOUTSIDE (HAx > (a.x + 1))
        #define ISGRIGHTOUTSIDE (ISGDRIGHTOUTSIDE && ISGARIGHTOUTSIDE)
    #define ISHDLEFTOUTSIDE (HDx < (a.x))
    #define ISHALEFTOUTSIDE (HAx < (a.x))
        #define ISHLEFTOUTSIDE (ISHDLEFTOUTSIDE && ISHALEFTOUTSIDE)
    #define ISGALEFTOUTSIDE (GAx < (a.x))
    #define ISGDLEFTOUTSIDE (GDx < (a.x))
        #define ISGLEFTOUTSIDE (ISGDLEFTOUTSIDE && ISGALEFTOUTSIDE)

    //Test if the pixel is completely outside of the 'ray'
    //(if all 4 intersection point x coordinates are either all less or all greater than the appropriate coordinates)
    if ((ISGLEFTOUTSIDE && ISHLEFTOUTSIDE) || (ISHRIGHTOUTSIDE && ISGRIGHTOUTSIDE))
        {
            return 0.0; //No effect on the pixels
        }
    //The 1.0 case can't occur if the angle is not exactly 90.0 or 0.0 degrees

    //Case 1; The l
    if (GDx < a.x)
        {
            register double LVI = 1 - (tana * (LVI.x - GDx)); //This is used in both branches
            //Check if GA.x is outside B.x -> We have to calculate a trapeze
            if (GAx > (LVI.x + 1.0))
                {
                    register double RVI;
                    RVI = 1 - (tana * (GAx - (LVI.x + 1)));
                    //Here a trapeze has been constructed using the secondary intersection points
                    //The trapeze height is the lower edge of the pixel (and thus equal to 1)
                    effect = (LVI + RVI) / 2;
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
                    effect = 0;

                }
        }
    return effect;
}
#endif	/* _FPMATH_HPP */

