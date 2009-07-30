/*
 * File:   main.cpp
 * Author: uli
 *
 * Created on 29. Juli 2009, 13:13
 */

#include <stdlib.h>
#include <string.h>

#define IMGPIX(i,x,y) images[i][(y) * width + (x)] //intvalue

#define MODE_HORIZONTAL 1
#define MODE_VERTICAL 2

/*
 *
 */
int main(int argc, char** argv)
{
    if (argc < 5) //Vertical/horizontal + 2 images
    {
        printf("Not enough arguments");
        printf("Usage: isect [h/v] [images]");
        exit(2);
    }

    //Check which mode (horizontal/vertical) to use
    int mode;
    if (strcmp(argv[1], "h") == 0 || strcmp(argv[1], "horizontal") == 0) {
        mode = MODE_HORIZONTAL;
    }
    else if (strcmp(argv[1], "v") == 0 || strcmp(argv[1], "vertical") == 0) {
        mode = MODE_VERTICAL;
    }
    else {
        printf("Invalid mode: %s", argv[1]);
        exit(0);
    }

    int imageCount = argc - 2;
    uint** images = (uint**) malloc(sizeof (uint*) * imageCount);
    uint* buffer;
    size_t imagesize, buffersize;
    int width, height;
    //Read all images
    LodePNG_Decoder decoder;
    LodePNG_Decoder_init(&decoder);
    for (int i = 0; i < imageCount; i++) {
        LodePNG_loadFile(&buffer, &buffersize, "/ram/x.png");
        LodePNG_decode(&decoder, &images[i], &imagesize, buffer, buffersize);
        width = decoder.infoPng.width;
        height = decoder.infoPng.height;
        free(buffer);
    }
    //Process the images
    LodePNG_Encoder encoder;
    LodePNG_Encoder_init(&encoder);
    LodePNG_InfoPng_copy(&encoder.infoPng, &decoder.infoPng);
    LodePNG_InfoRaw_copy(&encoder.infoRaw, &decoder.infoRaw); /*the decoder has written the PNG colortype in the infoRaw too*/

    //Allocate the images array
    uint** saveImages = malloc(sizeof (uint*) * imageCount); //new uint*[imageCount];
    for (int i = 0; i < imageCount; i++) {
        saveImages[i] = malloc(sizeof (uint) * width * height);
    }

    //Process the images

    if (mode == MODE_HORIZONTAL) {
        for (int i = 0; i < imageCount; i++) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    saveImages[y][x * imageCount + i] = images[i][y * width + x];
                }
            }
        }
    }

    else if (mode == MODE_VERTICAL) {
        for (int i = 0; i < imageCount; i++) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    saveImages[x][x * imageCount + i] = images[i][y * width + x];
                }
            }
        }
    }

    //Write all images
    for (int i = 0; i < imageCount; i++) {
    }

    LodePNG_Decoder_cleanup(&decoder);
    LodePNG_Encoder_cleanup(&decoder);
    return (EXIT_SUCCESS);
}

