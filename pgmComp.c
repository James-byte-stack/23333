#include "img.h"
int main(int argc, char **argv){
    //Error check for no parameter
    if(argc == 1){
        printf("Usage: ./pgmComp inputImage.pgm inputImage.pgm \n");
        return 0;
    }
    //Error check for wrong parameters
    if (argc != 3) {
        printf("ERROR: Bad Argument Count\n");
        return 1;
    }
    //read the data from two PGMImage
    PGMImage image1, image2;
    readPGMImage(argv[1],&image1);
    readPGMImage(argv[2],&image2);
    //compare
    if (comparePGMImage(&image1, &image2)) {
        printf("IDENTICAL\n");
    } else {
        printf("DIFFERENT\n");
    }
    //free the memory
    free(image1.pixels);
    free(image2.pixels);
    return 0;
}