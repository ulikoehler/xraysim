#ifndef SOBEL_H
#define SOBEL_H

#include <QImage>
#include <QtGui>
#include <cstdio>
#include <list>
#include <tr1/memory>
using namespace std;
using namespace std::tr1;

class Sobel
{
public:
    Sobel(shared_ptr<QImage> image);

    void smoothImage();
    shared_ptr<QImage> calculateSobelImage();

private:
    shared_ptr<QImage> image;
    ushort width;
    ushort height;

    int calculateSobel(ushort x, ushort y);
};

#endif // SOBEL_H
