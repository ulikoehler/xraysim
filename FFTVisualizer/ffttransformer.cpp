#include "ffttransformer.h"
#include <fftw3.h> //No need to link fftw3 when including the header

QSharedPointer<QImage> FFTTransformer::transformOne(QSharedPointer<QImage> input, short mode)
{
    int w = input->width();
    int h = input->height();

    fftw_complex* in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*w*h);
    fftw_complex* out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*w*h);

    //Create a plan for one-time usage (slightly suboptimal)
    fftw_plan plan;
    if(mode == FORWARD)
    {
        plan = fftw_plan_dft_2d(w,h,in,out,FFTW_FORWARD,FFTW_ESTIMATE);
    }
    else
    {
        plan = fftw_plan_dft_2d(w,h,in,out,FFTW_BACKWARD,FFTW_ESTIMATE);
    }

    //Load the data into the input array
    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            unsigned int i = input->pixel(x,y);
            in[y * w + x][0] = *reinterpret_cast<double*>(&i);
            in[y * w + x][1] = 0;
        }
    }

    //Do the calculation
    fftw_execute(plan);

    QSharedPointer<QImage> outputImage(new QImage(w,h,QImage::Format_ARGB32));
    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            //fftw_complex val;
            double greyValue = out[y * w + x][0];
            //int greyValue = val[0] * 255.0; //QColor(greyValue, greyValue, greyValue, greyValue).rgba()
            outputImage->setPixel(x,y,*reinterpret_cast<int*>(&greyValue));
        }
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return outputImage;
}
