/**************************\/
 *Brandon Torbay            *
 *Nikolaus Zampetopoulos    *
 *CPSC2310 Fall 2022        *
 *Email: btorbay@clemson.edu*
 *nzampet@clemson.edu       *
/ *************************/

#ifndef PPM_H_
#define PPM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef struct pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixel;

typedef struct image {
    int height;
    int width;
    int maxV;
    char magicNum[3];
    pixel** pixels;
} image;

/*
Parameters: width, height
Return: pixel**
This function uses malloc to allocate memory for the image pixels based on
the height/width values
*/
pixel** allocPixels(int width, int height);

/*
Parameters: image
Return: image
This function frees all previously allocated memory in an image  
*/
void freeImage(image** image);

/*
Parameters: input file
Return: image
This function uses the read header function and fread to read in an entire
image to allocated memory
*/
image* readPPM(FILE* input);

/*
Parameters: output file, image
Return: void
This function uses writeHeader and fwrite to create the new image file with a
header and correct pixel values
*/
void writePPM(FILE* output, image *image);

/* Parameters: Input file
Return: struct contaning header info
    This function reads the header of a ppm file to find height, width,
    magic num and max value. It uses the function discard() to remove 
    any comments in the original header. 
*/
image* readHeader(FILE* input);

/* Parameters: Input file
Return: void
This function reads through the header of the ppm file and removes any
comments When a comment is found, it skips to the next line of the header
and discards it
*/
void discard(FILE* input);

/* Parameters: Output file, cleaned up image
Return: void
This function uses fprintf to write the cleaned up header to the new ppm file
*/
void writeHeader(FILE* output, image *newHeader);

#endif