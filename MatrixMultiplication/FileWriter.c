#include "Matrices.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_LEN 10

void writeMatrix(int argc, int matIndex ,char* path) {
	if (matIndex >= numOfMats) {
		printf("matrix number to write is not found");
		exit(EXIT_FAILURE);
	}
	char* p;
	if (argc < 4) {
		printf("write on default file c.txt\n");
		asprintf(&p, "%s", "files/c.txt");
	}else{
		asprintf(&p, "%s%s", "files/", path);
	}
	FILE *f;
	f = fopen(p, "w");
	if (f != NULL) {
		setMatrix(matIndex, f);
		fclose(f);
	} else {
		perror(path); /* why didn't the file open? */
		exit(EXIT_FAILURE);
	}
}

void setMatrix(int matIndex, FILE* f) {
	int r = matrices[matIndex]->r, c = matrices[matIndex]->c;
	int size = ((MAX_NUM_LEN + 2) * c + 2) * r;
	char* matRow = malloc(size * sizeof(char*));
	memset(matRow, 0, size);
	char buff[11];
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			memset(buff, 0, 11);
			sprintf(buff, "%d", matrices[matIndex]->mat[i][j]);
			strcat(matRow, buff);
			strcat(matRow, "\t");
		}
		strcat(matRow, "\n");
	}
	fprintf(f, "%s\n", matRow);
	free(matRow);
}
