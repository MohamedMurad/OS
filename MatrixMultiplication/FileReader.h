#ifndef FILE_READER_H_   /* Include guard */
#define FILE_READER_H_

/**
 * initialize a dynamic local 2d matrix at file reader.
 */
void initializeFileReaderMatrix();

/**
 * destroy the dynamic allocated local 2d matrix at file reader.
 */
void destroyFileReaderMatrix();

/* 
 this function read matrix on the following standards"
 1- first line determines number of rows and number of cols
 2- each column is separated with '\n'
 3- each row is separated with '\t'
 else, it will throw error.
 */
void readMatrix(char* path);

/**
 * getter for number of read row.
 */
int getNumOfRow();

/**
 * getter for number of read col.
 */
int getNumOfCol();

/**
 * getter for read matrix.
 */
int** getMat();

#endif // FILE_READER_H_
