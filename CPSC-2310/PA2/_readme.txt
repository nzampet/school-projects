/**************************\/
 *Brandon Torbay            *
 *Nikolaus Zampetopoulos    *
 *CPSC2310 Fall 2022        *
 *Email: btorbay@clemson.edu*
 *nzampet@clemson.edu       *
/ *************************/

/*

We had problems with not reading and writing in binary on windows because fwrite would append carriage return to the output
file and it would look like a corrupted image. We also had problems in our bitwise equation because of forgetting parenthesis
and with the order of the columns and rows when allocating/looping over them. We also had problems when trying to read in an
entire line from the console input but we found a solution using the scanset feature of scanf. We avoided many issues by coding
incrementally and testing things such as the bitwise equations seperately before using them in our code. I solved the windows
issue and others by analyzing the output files in hex and text editors. I enjoyed this project because it was a good challenge
without getting too complicated with memory allocation and data structures. This wasn't my first time using or learning bitwise
operators but I think it was a good test to get students thinking of how to use them. In our code we used bitwise operations in
both the encoding and decoding. In the encoding we used the AND operator for a mask to get a single bit and used left and right
shifts to perform the mask correctly. In the decoding function we used the left shift operator to add a single bit to a number
at a time.

*/