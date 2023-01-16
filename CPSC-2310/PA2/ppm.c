/**************************\/
 *Brandon Torbay            *
 *Nikolaus Zampetopoulos    *
 *CPSC2310 Fall 2022        *
 *Email: btorbay@clemson.edu*
 *nzampet@clemson.edu       *
/ *************************/

#include "ppm.h"

pixel** allocPixels(int width, int height) {
    pixel** pixels = (pixel**)malloc(sizeof(pixel*) * height);
    pixels[0] = (pixel*)malloc(sizeof(pixel) * width * height);
    
    for(int i = 1; i < height; i++)
        pixels[i] = (*pixels + width * i);

    return pixels;
}

void freeImage(image** image) {
    free((*image)->pixels[0]);
    free((*image)->pixels);
    free(*image);
    *image = NULL;
}

image* readPPM(FILE* input) {
    image* newImage = readHeader(input);

    newImage->pixels = allocPixels(newImage->width, newImage->height);
    fread(newImage->pixels[0], sizeof(pixel), newImage->width * newImage->height, input);

    return newImage;
}

void writePPM(FILE* output, image *image) {
    writeHeader(output, image);
    fwrite(image->pixels[0], sizeof(pixel), image->width * image->height, output);
}

image* readHeader(FILE* input) {
    //Create image
    image* newImage = (image*)malloc(sizeof(image));

    //reading magic number
    fscanf(input, "%s", newImage->magicNum);
    //discarding comments
    discard(input);
    //using scanf to scan width, height and max val
    //discarding comments after every call
    fscanf(input, "%u", &newImage->width);
    discard(input);
    fscanf(input, "%u", &newImage->height);
    discard(input);
    fscanf(input, "%u", &newImage->maxV);
    //Skip whitespace
    fgetc(input);
    //assert to ensure valid format for program (P6 & max val of 255)
    assert(!strcmp(newImage->magicNum, "P6"));
    assert(newImage->maxV <= 255);
    //Safeguard against errors
    newImage->pixels = NULL;

    return newImage;
}

void discard(FILE* input) {
    //Repeat for multiple lines
    char tmpChar = '\0';
    while (!feof(input) && !isdigit(tmpChar)) {
        //Read until first comment or number
        while (!feof(input) && tmpChar != '#' && !isdigit(tmpChar)) {
            tmpChar = getc(input);
        }

        //If comment then read until a newline and if not then back up one
        //for numbers
        if (tmpChar == '#') {
            while (!feof(input) && tmpChar != '\n') {
                tmpChar = getc(input);
            }
        } else {
            ungetc(tmpChar, input);
        }
    }
}

void writeHeader(FILE* output, image *newHeader) {
    //using fprintf to write header information to ppm file
    fprintf(output,"%s\n", newHeader->magicNum);
    fprintf(output,"%d ", newHeader->width);
    fprintf(output,"%d ", newHeader->height);
    fprintf(output,"%d\n", newHeader->maxV);
    return;
}