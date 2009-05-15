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
    //this->image = newImage;
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

    //TODO Check if optimization is needed
    int hsobel = pixels[0] + (pixels[3] * 2) + pixels[6]
            - pixels[2] - (pixels[5] * 2) - pixels[8];
    int vsobel = pixels[0] + (pixels[1] * 2) + pixels[3]
             - pixels[6] - (pixels[7] * 2) - pixels[8];

    int res = vsobel + hsobel;
    if(res < 0) {res *= -1;}
    return res;
}

shared_ptr<QImage> Sobel::calculateSobelImage()
{

    shared_ptr<QImage> sobelImage(new QImage(width, height, QImage::Format_RGB32));
    for (int w = 0; w < width;w++)
    {
        for(int h = 0; h < height; h++)
        {

        }
    }
    //image->setPixel(w, h, (uint) hsobel + vsobel);
}
