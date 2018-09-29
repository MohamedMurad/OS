#include "Matrices.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initializeMats(int numOfMatrices) {
	numOfMats = numOfMatrices;
	matrices = malloc(numOfMats * sizeof(struct matrix));
}

void addMatrix(int row, int col, int** mat, int index) {
	initializeMat(row, col, index);
	matrices[index]->mat = mat;
}

void initializeMat(int row, int col, int index) {
	if (index >= numOfMats) {
		printf("number of matrix reached max1\n");
		exit(EXIT_FAILURE);
	}
	struct matrix *mat = (struct matrix *) malloc(sizeof(struct matrix));
	mat->r = row;
	mat->c = col;
	matrices[index] = mat;
}

void destroyMats() {
	printf("strat destroyMats\n");
	for (int i = 0; i < numOfMats; i++) {
		free(matrices[i]);
	}
	free(matrices);
	printf("finish destroyMats\n");
}

void printMatrix(int index) {
	if (index >= numOfMats) {
		printf("number of matrix reached max2\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < matrices[index]->r; ++i) {
		for (int j = 0; j < matrices[index]->c; ++j) {
			printf("%d\t", matrices[index]->mat[i][j]);
		}
		printf("\n");
	}
}
