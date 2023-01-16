/**************************\/
 *Brandon Torbay            *
 *Nikolaus Zampetopoulos    *
 *CPSC2310 Fall 2020        *
 *Email: btorbay@clemson.edu*
 *nzampet@clemson.edu       *
/ *************************/
#include "EncodeDecode.h"

int main(int argc, char* argv[]) {
    assert(argc == 3);
    FILE* input = fopen(argv[1], "rb");
    assert(input != NULL);
    FILE* output = fopen(argv[2], "wb");
    assert(output != NULL);

    int choice = 1;
    char message[250];
    printf("Welcome to the image encoder, please select option below:\n");
    printf("1: Use provided input message\n2: Enter unique input message\n");
    printf("Option: ");
    scanf("%d", &choice);
    if (choice == 1) {
        strcpy(message, "Standard message to be encoded");
        encodeToImage(input, output, message);
    } else if (choice == 2) {
        printf("Enter your unique input message: ");
        getchar();
        scanf("%249[^\n]", message);
        encodeToImage(input, output, message);
        printf("Thank you for the message\n");
    }
    
    fclose(input);
    fclose(output);

    input = fopen(argv[2], "rb");
    char* decodedMsg = decodeFromImage(input);
    printf("Message: %s", decodedMsg);

    free(decodedMsg);
    fclose(input);

    return 0;
}