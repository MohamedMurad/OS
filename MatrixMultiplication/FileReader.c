#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_LINE_SIZE 50
#define MAX_NUM_LEN 10

long r = 0, c = 0;
int countFileRead = 0;
int** mat;

int** getMat() {
	return mat;
}

int getNumOfRow() {
	return r;
}

int getNumOfCol() {
	return c;
}

void initializeFileReaderMatrix() {
	mat = malloc(r * sizeof(int*));
	for (int i = 0; i < r; i++) {
		mat[i] = malloc(c * sizeof(int));
	}
}

void readMatrix(char* path) {
	char* p;
	if (countFileRead != 0 || path == NULL || strcmp(path, "") == 0) {
		if (countFileRead == 0) {
			printf("open default file a.txt\n");
			asprintf(&p, "%s", "files/a.txt");
		} else {
			printf("open default file b.txt\n");
			asprintf(&p, "%s", "files/b.txt");
		}
		countFileRead++;
	} else {
		asprintf(&p, "%s%s", "files/", path);
	}
	FILE *f;
	f = fopen(p, "r");
	if (f != NULL) {
		//set number of rows and number of cols.
		setBounds(f);
		//set the matrix.
		getMatrix(f);
		fclose(f);
	} else {
		perror(path); /* why didn't the file open? */
		exit(EXIT_FAILURE);
	}

}

void getMatrix(FILE* f) {
	initializeFileReaderMatrix();
	int size = (MAX_NUM_LEN + 2) * c + 2;
	char line[size];
	int rowIdx = 0, colIdx = 0;
	char delim[] = " \t\n";
	while (fgets(line, sizeof(line), f) != NULL) {
		colIdx = 0;
		for (char *token = strtok(line, delim); token != NULL;
				token = strtok(NULL, delim)) {
			if (isNumeric(token) == 1) {
				if (rowIdx < r && colIdx < c) {
					mat[rowIdx][colIdx] = atoi(token);
				} else {
					errorTermination("out of bounds our matrix");
				}

			} else {
				errorTermination("not numeric element in matrix");
			}
			colIdx++;
		}
		if (colIdx != c) {
			errorTermination("missing columns elements");
		}
		rowIdx++;
	}
	if (rowIdx != r) {
		errorTermination("missing rows elements");
	}
}

void setBounds(FILE* f) {
	char line[FIRST_LINE_SIZE];
	fgets(line, sizeof(line), f);/* read a line */
	if (line == NULL) {
		errorTermination("first line.");
	} else {
		char delim[] = " =\t\n";
		char* token;
		token = strtok(line, delim);
		if (strcmp(token, "row") != 0) {
			errorTermination("\"row\" isn't determined");
		}
		token = strtok(NULL, delim);
		if (isNumeric(token) == 1) {
			r = atoi(token);
		} else {
			errorTermination("in number of rows");
		}
		token = strtok(NULL, delim);
		if (strcmp(token, "col") != 0) {
			errorTermination("\"col\" isn't determined");
		}
		token = strtok(NULL, delim);
		if (isNumeric(token) == 1) {
			c = atoi(token);
		} else {
			errorTermination("in number of columns");
		}
		token = strtok(NULL, delim);
		if (token != NULL) {
			errorTermination(
					"first line isn't on this construction \"row=int col=int\"");
		}
	}
}

void errorTermination(char* message) {
	printf("error : %s\n", message);
	exit(EXIT_FAILURE);
}

/*
 * return 1 if str is number.
 * return -1 if isn't a number.
 */
int isNumeric(char* str) {
	int i = 0;
	if (str[i] == '-') {
		i++;
	}
	while (str[i] != '\0') {
		if (!isdigit(str[i])) {
			return -1;
		}
		i++;
	}
	return 1;
}

