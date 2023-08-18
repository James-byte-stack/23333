//
// Created by James's pc on 2023/8/9.
//

#ifndef IMG_H
#define IMG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMENT_LINE_LENGTH 128
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536

typedef struct {
    int width;
    int height;
    int maxGrayValue;
    unsigned char* pixels;
} PGMImage;

int readPGMImage( char* filename, PGMImage* image);
int writePGMImage( char* filename,  PGMImage* image, char format);
int readPGMFormat(  char* filename);
int convertPGMImage( char* inputFile,  char* outputFile);
int pgma2b( char *inputFile,  char *outputFile);
int pgmb2a( char *inputFile,  char *outputFile);
int comparePGMImage( PGMImage *image1,  PGMImage *image2);
int reducePGMImage(  char* input_file, int factor,  char* output_file);
#endif //IMG_H
