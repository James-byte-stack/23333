#include "img.h"
int readPGMImage( char* filename, PGMImage* image){
    //Open the file
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("ERROR: Bad File Name (%s)\n", filename);
        return 2;
    }
    // Read the head of the file
    char magicNumber[3];
    fscanf(file, "%2s\n", magicNumber);
    if (strcmp(magicNumber, "P2") != 0||strcmp(magicNumber, "P5") != 0) {
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        fclose(file);
        return 3;
    }
    //comment line
    char *commentLine = NULL;
    char nextChar = fgetc(file);
    int scanCount = fscanf(file, " ");
    if (nextChar == '#')
    {
        commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
        char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, file);
        if (commentString == NULL)
            free(commentLine);
            fclose(file);
            printf("ERROR: Bad Comment Line (%s)\n", filename);
            return 4;
    }
    else
        ungetc(nextChar, file);
    //read width and height
    scanCount = fscanf(file, " %u %u %u", &(image->width), &(image->height), &(image->maxGrayValue));
    fscanf(file, "%d %d\n", &(image->width), &(image->height));
    if (
            (scanCount != 3	)	||
            (image->width < MIN_IMAGE_DIMENSION	) 	||
            (image->width > MAX_IMAGE_DIMENSION	) 	||
            (image->height < MIN_IMAGE_DIMENSION	) 	||
            (image->height > MAX_IMAGE_DIMENSION	)
    )
    {
        printf("ERROR: Bad Dimensions (%s)\n", filename);
        free(commentLine);
        fclose(file);
        return 5;
    }
    //read maxGrayValue
    int maxGrayValue;
    fscanf(file, "%d\n", &maxGrayValue);
    if (maxGrayValue <= 0 || maxGrayValue > 255) {
        printf("ERROR: Bad Max Gray Value (%s)\n", filename);
        free(commentLine);
        fclose(file);
        return 6;
    }
    //allocate image memory
    image->pixels = (unsigned char*) malloc(image->width * image->height * sizeof(unsigned char));
    if (image->pixels == NULL) {
        printf("ERROR: Image Malloc Failed\n");
        fclose(file);
        return 7;
    }
    //read pixels
    size_t bytesRead = fread(image->pixels, sizeof(unsigned char), image->width * image->height, file);
    if (bytesRead != image->width * image->height) {
        free(image->pixels);
        fclose(file);
        printf("ERROR: Bad Data (%s)\n", filename);
        return 8;
    }
    return 0;
}

int writePGMImage( char* filename,  PGMImage* image, char format){
    //Open the file
    FILE* file = fopen(filename, "wb");
    int i;
    if (file == NULL) {
        printf("ERROR: Bad File Name (%s)\n", filename);
        return 2;
    }
    fprintf(file, "P%d\n", format);
    fprintf(file, "%d %d\n", image->width, image->height);

    // Write image data
    if (format == 2) {
        for ( i = 0; i < image->width * image->height; i++) {
            fprintf(file, "%hhu ", image->pixels[i]);
        }
    } else if (format == 5) {
        fwrite(image->pixels, sizeof(unsigned char), image->width * image->height, file);
    }
    fclose(file);
    return 0;
}

int readPGMFormat( char* filename) {
    FILE *inputFile = fopen(filename, "rb");
    if (inputFile == NULL) {
        printf("ERROR: Bad File Name (%s)\n", filename);
        return 0;
    }
    char format[3];
    fgets(format, sizeof(format), inputFile);
    fclose(inputFile);
    int formatNum = atoi(format + 1);
    return formatNum;
}

int convertPGMImage( char* inputFile,  char* outputFile){
PGMImage image;
    int i ;
    int j ;
int readResult = readPGMImage(inputFile,&image);
    if (readResult != 0) {
        return readResult;
    }
    // create a 2-dimensional matrix to store pixel values
    unsigned char** matrix = (unsigned char**) malloc(image.height * sizeof(unsigned char*));
    for ( i = 0; i < image.height; i++) {
        matrix[i] = &(image.pixels[i * image.width]);
    }

    // print the pixel values of the 2-dimensional matrix


    for ( i = 0 ; i < image.height; i++) {
        for ( j = 0; j < image.width; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free the memory allocated for the matrix
    free(matrix);
    int saveResult = writePGMImage(outputFile, &image,2);
    if (saveResult != 0) {
        return saveResult;
    }

    return 0;
}
int pgma2b( char *inputFile,  char *outputFile) {
    PGMImage image;

    if (!readPGMImage(inputFile, &image)) {
        printf("ERROR: Bad Data (%s)\n", inputFile);
        return 8;
    }

    if (!writePGMImage(outputFile, &image, 5)) {
        printf("ERROR: Output Failed (%s)\n", outputFile);
        free(image.pixels);
        return 9;
    }
    free(image.pixels);
    return 0;
}

int pgmb2a( char *inputFile,  char *outputFile) {
    PGMImage image;

    if (!readPGMImage(inputFile, &image)) {
        printf("ERROR: Bad Data (%s)\n", inputFile);
        return 8;
    }

    if (!writePGMImage(outputFile, &image, 2)) {
        printf("ERROR: Output Failed (%s)\n", outputFile);
        free(image.pixels);
        return 9;
    }
    free(image.pixels);
    return 0;
}

int comparePGMImage( PGMImage *image1,  PGMImage *image2){
    int i;
    if (image1->width != image2->width || image1->height != image2->height) {
        return 0;
    }

    for ( i = 0; i < image1->width * image1->height; i++) {
        if (image1->pixels[i] != image2->pixels[i]) {
            return 0;
        }
    }

    return 1;
}
int reducePGMImage(  char* inputFile, int factor,  char* outputFile){
    PGMImage input_image;
    int i;
    int j;
    if (readPGMImage(inputFile, &input_image) != 0) {
        printf("ERROR: Bad Data (%s)\n", inputFile);
        return 8;
    }
    int new_width = input_image.width / factor;
    int new_height = input_image.height / factor;
    PGMImage output_image;
    output_image.width = new_width;
    output_image.height = new_height;
    output_image.pixels = (unsigned char*) malloc(new_width * new_height * sizeof(unsigned char));
    if (output_image.pixels == NULL) {
        printf("ERROR: Image Malloc Failed\n");
        free(input_image.pixels);
        return 7;
    }
    for ( i = 0; i < new_height; i++) {
        for ( j = 0; j < new_width; j++) {
            int input_index = (i * factor) * input_image.width + (j * factor);
            int output_index = i * new_width + j;
            output_image.pixels[output_index] = input_image.pixels[input_index];
        }
    }
    if (writePGMImage(outputFile, &output_image, readPGMFormat(inputFile)) != 0) {
        free(input_image.pixels);
        free(output_image.pixels);
        printf("ERROR: Output Failed (%s)\n", outputFile);
        return 9;
    }
    free(input_image.pixels);
    free(output_image.pixels);
    return 0;
}