/**************************\/
 *Brandon Torbay            *
 *Nikolaus Zampetopoulos    *
 *CPSC2310 Fall 2022        *
 *Email: btorbay@clemson.edu*
 *nzampet@clemson.edu       *
/ *************************/

#ifndef ENCODEDECODE_H_
#define ENCODEDECODE_H_

#include "ppm.h"

typedef struct linkedStr {
    char ch;
    struct linkedStr* next;
} linkedStr;

/*
Parameters: Output file pointer, char* string
Return : void
This function encodes a message to an image by taking the current pixel value,
subtracting the mod 10 of the value from the original value, bitwise shifting
left by the index * 3 - 1 and then index * 3 - 1
*/
void encodeToImage(FILE* input, FILE* output, char* string);
/*
Parameters: Input file pointer
Return: char*
This code decodes a message from an image by finding the mod 10 of the pixel
value and bitwise shifting it left by 1
*/
char* decodeFromImage(FILE* input);

#endif