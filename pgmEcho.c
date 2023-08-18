/***********************************/
/* XJCO 1921M Programming Project  */
/* 2022-23 Spring Semester         */
/*           			   */
/*                                 */
/* Version 0.2: Zheng Wang         */
/* Version 0.1: Hamish Carr        */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in ASCII and echo the data */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>
/* library for memory routines     */
#include <stdlib.h>
#include "img.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{
    //Error check for no parameter
    if(argc == 1){
        printf("Usage: ./pgmEcho inputImage.pgm outputImage.pgm \n");
        return 0;
    }
    //Error check for wrong parameters
    if (argc != 3) {
        printf("ERROR: Bad Argument Count\n");
        return 1;
    }
     char* inputFile = argv[1];
     char* outputFile = argv[2];
     //covert the PGMImage
    int convertResult = convertPGMImage(inputFile, outputFile);
    if (convertResult != 0) {
        return convertResult;
    }
    printf("ECHOED\n");
    return 0;
}
