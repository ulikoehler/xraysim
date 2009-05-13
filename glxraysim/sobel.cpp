#include "sobel.h"

Sobel::Sobel(shared_ptr<QImage> imageParam)
{
    image = imageParam;
    height = image->height();
    width = image->width();
}

void Sobel::smoothImage()
{
    int pixels[9];
    shared_ptr<QImage> newImage(new QImage(width, height, QImage::Format_RGB32));
    for(int y = 1; y < image->height() -1; y++)
    {
        for(int x = 1; x < image->width() - 1;x++)
        {
            //get the pixel values
            // 0 1 2
            // 3 4 5
            // 6 7 8
            pixels[0] = qGray(image->pixel(x - 1, y - 1));
            pixels[1] = qGray(image->pixel(x, y - 1));
            pixels[2] = qGray(image->pixel(x + 1, y - 1));
            pixels[3] = qGray(image->pixel(x - 1, y));
            pixels[4] = qGray(image->pixel(x, y));
            pixels[5] = qGray(image->pixel(x + 1, y));
            pixels[6] = qGray(image->pixel(x - 1, y + 1));
            pixels[7] = qGray(image->pixel(x, y + 1));
            pixels[8] = qGray(image->pixel(x + 1, y + 1));

            //Mask:
            // 1 2 1
            // 2 4 2
            // 1 2 1

            int val = (pixels[0] + (2 * pixels[1]) + pixels[2]
                      + (2 * pixels[3]) + (4 * pixels[4]) + (2 * pixels[5])
                      + pixels[6] + (2 * pixels[7]) + pixels[8]) / 8;

            newImage->setPixel(x,y,val);
        }
    }
    this->image = newImage;
}

int Sobel::calculateSobel(ushort x, ushort y)
{
    int pixels[9]; //Pixels around the scoped pixel
    //get the pixel values
    // 0 1 2
    // 3 4 5
    // 6 7 8
    pixels[0] = qGray(image->pixel(x - 1, y - 1));
    pixels[1] = qGray(image->pixel(x, y - 1));
    pixels[2] = qGray(image->pixel(x + 1, y - 1));
    pixels[3] = qGray(image->pixel(x - 1, y));
    //pixels[4] is not needed
    pixels[5] = qGray(image->pixel(x + 1, y));
    pixels[6] = qGray(image->pixel(x - 1, y + 1));
    pixels[7] = qGray(image->pixel(x, y + 1));
    pixels[8] = qGray(image->pixel(x + 1, y + 1));

    int hsobel = pixels[0] + (pixels[3] * 2) + pixels[6]
            - pixels[2] - (pixels[5] * 2) - pixels[8];
    int vsobel = pixels[0] + (pixels[1] * 2) + pixels[3]
             - pixels[6] - (pixels[7] * 2) - pixels[8];

    int res = vsobel + hsobel;
    if(res < 0) {res *= -1;}
    return res;
}

std::list<Point> Sobel::startAtPoint(ushort startX, ushort startY, Direction d)
{
    std::list<Point> points;

    ushort x = 0;
    ushort y = 0;

    //Find the first pixel having a gradient
    for(x = startX; x < width;x++)
    {
        int sob = calculateSobel(x, y);
        if (sob > 1000) {break;}
    }

    Point beginPoint;
    beginPoint.x = x;
    beginPoint.y = y;

    std::list<Point> vertices;

    //As the scoped pixel mustn't be the maximum again, this has only 8 elements
    int sobels[8]; //Sobels of the pixels around the scoped pixel
    while(true)
    {
        Point p;
        p.x = x;
        p.y = y;
        vertices.push_back(p);

        //If we reached the beginning
        if(p.x == beginPoint.x && p.y == beginPoint.y)
        {
            break;
        }

        sobels[0] = calculateSobel(x - 1, y - 1);
        sobels[1] = calculateSobel(x, y - 1);
        sobels[2] = calculateSobel(x + 1, y - 1);
        sobels[3] = calculateSobel(x - 1, y);
        sobels[4] = calculateSobel(x + 1, y);
        sobels[5] = calculateSobel(x - 1, y + 1);
        sobels[6] = calculateSobel(x, y + 1);
        sobels[7] = calculateSobel(x + 1, y + 1);

        int max = -1;
        int maxindex = -1;
        for(int i = 0;i < 8; i++)
        {
            if (sobels[i] > max) {max = sobels[i];maxindex = i;}
        }

        switch(maxindex)
        {
            case 0: {x -= 1; y -= 1;break;}
            case 1: {y -= 1;break;}
            case 2: {x += 1; y -= 1;break;}
            case 3: {x -= 1;break;}
            //case 4: {} //Can't occur; nothing to change
            case 4: {x += 1;break;}
            case 5: {x -= 1; y += 1;break;}
            case 6: {y += 1;break;}
            case 7: {x += 1; y += 1;break;}
            default: break;
        }
    }


    //Calculate x sobel
    //TODO Check if optimization is needed
    //image->setPixel(w, h, (uint) hsobel + vsobel);
}
