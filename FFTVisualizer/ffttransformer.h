#ifndef FFTTRANSFORMER_H
#define FFTTRANSFORMER_H
#include <QtGui>

class FFTTransformer
{
public:
     static const short FORWARD = 0;
     static const short INVERSE = 1;
     static QSharedPointer<QImage> transformOne(QSharedPointer<QImage> input, short mode);
};

#endif // FFTTRANSFORMER_H
