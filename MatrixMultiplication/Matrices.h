#ifndef MATRICIES_H_   /* Include guard */
#define MATRICIES_H_

/**
 * number of matrices.
 */
int numOfMats;

/**
 * each matrix represented by this structure.
 */
struct matrix {
	int r, c;
	int** mat;
};


/**
 * list of our matrices.
 */
struct matrix **matrices;


/**
 * set used matrices.
 */
void initializeMats(int numOfMatrices);

/**
 * this function used to add matrix to our list of matrices.
 */
void addMatrix(int row, int col, int** mat, int index);

/**
 * destroy all matrices.
 */
void destroyMats();

/**
 * print our matrix.
 */
void printMatrix(int index);

#endif // MATRICIES_H_
