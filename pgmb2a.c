#include "img.h"
int main(int argc, char **argv){
    //Error check for no parameter
    if(argc == 1){
        printf("Usage: ./pgmb2a inputImage.pgm outputImage.pgm \n");
        return 0;
    }
    //Error check for wrong parameters
    if (argc != 3) {
        printf("ERROR: Bad Argument Count\n");
        return 1;
    }
    int covertResult = pgmb2a(argv[1],argv[2]);
    if (covertResult != 0) {
        return covertResult;
    }
    printf("CONVERTED\n");
}