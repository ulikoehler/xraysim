/*
 * File:   main.cpp
 * Author: uli
 *
 * WARNING: This program may be vulnerable to format string attacks
 *
 * Created on 29. Juli 2009, 13:13
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lodepng.h"

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

    char** inputImageFilenames = argv + 2;
    //Check which mode (horizontal/vertical) to use
    char directionSpecifier[2];
    int mode;
    if (strcmp(argv[1], "h") == 0 || strcmp(argv[1], "horizontal") == 0) {
        mode = MODE_HORIZONTAL;
        strcpy(directionSpecifier, "h");
    }
    else if (strcmp(argv[1], "v") == 0 || strcmp(argv[1], "vertical") == 0) {
        mode = MODE_VERTICAL;
        strcpy(directionSpecifier, "v");
    }
    else {
        printf("Invalid mode: %s", argv[1]);
        exit(0);
    }

    int inputImageCount = argc - 2;
    unsigned char** images = (unsigned char**) malloc(sizeof (unsigned char*) * inputImageCount * 4);
    unsigned char* buffer;
    size_t imagesize, buffersize;
    int width, height;
    //Read all images
    LodePNG_Decoder decoder;
    LodePNG_Decoder_init(&decoder);
    for (int i = 0; i < inputImageCount; i++) {
        LodePNG_loadFile(&buffer, &buffersize, inputImageFilenames[i]);
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

    //Calculate the extends of the images to be saved
    int saveImageWidth = -1;
    int saveImageHeight = -1;
    size_t saveImageCount = -1;
    if (mode == MODE_HORIZONTAL) {
        saveImageHeight = width;
        saveImageWidth = inputImageCount;
        saveImageCount = height;
    }
    else if (mode == MODE_VERTICAL) {
        saveImageHeight = height;
        saveImageWidth = inputImageCount;
        saveImageCount = width;
    }

    //Allocate the images array
    unsigned char** saveImages = malloc(sizeof (unsigned char*) * saveImageCount);
    for (int i = 0; i < inputImageCount; i++) {
        saveImages[i] = malloc(sizeof (unsigned char) * saveImageWidth * saveImageHeight);
    }

    //Process the images

    if (mode == MODE_HORIZONTAL) {
        for (int i = 0; i < inputImageCount; i++) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    saveImages[y][x * inputImageCount + i] = images[i][y * width + x];
                }
            }
        }
    }

    else if (mode == MODE_VERTICAL) {
        for (int i = 0; i < inputImageCount; i++) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    saveImages[x][x * inputImageCount + i] = images[i][y * width + x];
                }
            }
        }
    }

    //Free the input image memory
    for (int i = 0; i < inputImageCount; i++) {
        free(images[i]);
    }
    free(images);

    //Write all images and free the memory
    for (unsigned i = 0; i < inputImageCount; i++) {
        LodePNG_encode(&encoder, &buffer, &buffersize, saveImages[i], decoder.infoPng.width, decoder.infoPng.height);
        //Construct the output filename string...
        char* filenameBuffer = (char*) malloc(sizeof (char) * strlen(inputImageFilenames[i]) + 256); //256 should be enough to hold the direction specifier number
        sprintf(filenameBuffer, "%s-%s-%i.png", inputImageFilenames[i], directionSpecifier, i);
        //...and write the image to the associated file
        LodePNG_saveFile(buffer, buffersize, filenameBuffer);
        //Free the unneeded data
        free(filenameBuffer);
        free(saveImages[i]);
    }

    free(saveImages);


    LodePNG_Decoder_cleanup(&decoder);
    LodePNG_Encoder_cleanup(&decoder);
    return (EXIT_SUCCESS);
}

