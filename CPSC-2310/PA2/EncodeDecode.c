/**************************\/
 *Brandon Torbay            *
 *Nikolaus Zampetopoulos    *
 *CPSC2310 Fall 2022        *
 *Email: btorbay@clemson.edu*
 *nzampet@clemson.edu       *
/ *************************/

#include "EncodeDecode.h"

void encodeToImage(FILE* input, FILE* output, char* string) {
    image* myImage = readPPM(input);

    int strIndex = 0,
        numIndex = 3;
    for (int y = 0; y < myImage->height; y++) {
        for (int x = 0; x < myImage->width; x++) {
            char currChar = string[strIndex];
            pixel* currPixel = &myImage->pixels[y][x];
            currPixel->r -= (currPixel->r % 10) + (currChar >>
                                    (numIndex * 3 - 1) & 1);
            currPixel->g -= (currPixel->g % 10) + (currChar >>
                                    (numIndex * 3 - 2) & 1);
            currPixel->b -= (currPixel->b % 10) + (currChar >>
                                    (numIndex * 3 - 3) & 1);
            numIndex--;
            if (numIndex == 0) {
                numIndex = 3;
                strIndex++;
                if (string[strIndex] == '\0') {
                    y = myImage->height;
                    break;
                }
            }
        }
    }

    writePPM(output, myImage);
    freeImage(&myImage);
}

char* decodeFromImage(FILE* input) {
    image* myImage = readPPM(input);
    //current value of pixel and size of message to be decoded
    int currVal = 0, messageSize = 0;; 
    //allocating memory
    linkedStr* head = (linkedStr*)malloc(sizeof(linkedStr));
    linkedStr* currChar = head;
    //decoding pixels for message
    for (int y = 0; y < myImage->height; y++) {
        for (int x = 0; x < myImage->width; x++) {
            pixel* currPixel = &myImage->pixels[y][x];
            currVal <<= 1;
            currVal += currPixel->r % 10;
            currVal <<= 1;
            currVal += currPixel->g % 10;
            currVal <<= 1;
            currVal += currPixel->b % 10;
            // check for any pixels not using our encoding and end if found
            if (currPixel->r % 10 > 1 || currPixel->g % 10 > 1 ||
                                         currPixel->b % 10 > 1) {
                y = myImage->height;
                break;
            }
            // once we get the three pixel values 
            if ((x + y) % 3 == 2) {
                messageSize++;
                currChar->ch = (char)currVal;
                currVal = 0;
                // allocating memory for next char
                currChar->next = (linkedStr*)malloc(sizeof(linkedStr));
                currChar = currChar->next;
                currChar->next = NULL;
            }
        }
    }
    int msgIndex = 0;
    char* message = (char*)malloc(sizeof(char) * messageSize + 1);
    currChar = head;
    //freeing memory
    while (currChar->next) {
        message[msgIndex++] = currChar->ch;
        linkedStr* oldLS = currChar;
        currChar = currChar->next;
        free(oldLS);
    }
    free(currChar);
    message[msgIndex] = '\0';
    freeImage(&myImage);
    return message;
}