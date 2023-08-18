#include "img.h"
int main(int argc, char **argv){
    //Error check for no parameter
    if(argc == 1){
        printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm \n");
        return 0;
    }
    //Error check for wrong parameters
    if (argc != 4) {
        printf("ERROR: Bad Argument Count\n");
        return 1;
    }
    //reduce
    int reduceResult = reducePGMImage(argv[1], atoi(argv[2]), argv[3]);
    if (reduceResult != 0) {
        return reduceResult;
    }
    printf("REDUCED\n");
    return 0 ;

}