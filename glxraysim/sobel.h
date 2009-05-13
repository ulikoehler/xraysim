#ifndef SOBEL_H
#define SOBEL_H

#include <QImage>
#include <QtGui>
#include <cstdio>
#include <list>
#include <tr1/memory>
using namespace std;
using namespace std::tr1;

/**
 * Enums
 */

enum Direction
{
    HORIZONTAL,
    VERTICAL
};

/**
 * Structs
 */
struct Point
{
    ushort x;
    ushort y;
};

class Sobel
{
public:
    Sobel(shared_ptr<QImage> image);

    void smoothImage();
    std::list<Point> startAtPoint(ushort x, ushort y, Direction d);

private:
    shared_ptr<QImage> image;
    ushort width;
    ushort height;

    int calculateSobel(ushort x, ushort y);
};

#endif // SOBEL_H
