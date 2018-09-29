#include "Matrices.h"
#include "Color.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>


long r1, r2, r3, c1, c2, c3;
int **mat, **mat1, **mat2;

struct pair {
	int r, c;
};


void initializeMethodsMats(int matIndex1, int matIndex2) {
	r1 = matrices[matIndex1]->r;
	c1 = matrices[matIndex1]->c;
	r2 = matrices[matIndex2]->r;
	c2 = matrices[matIndex2]->c;
	r3 = r1;
	c3 = c2;
	if (c1 != r2) {
		printf("can't multiply the two matrices\n");
		exit(EXIT_FAILURE);
	}
	mat = malloc(r3 * sizeof(int*));
	for (int i = 0; i < r3; i++) {
		mat[i] = malloc(c3 * sizeof(int));
	}
	mat1 = malloc(r1 * sizeof(int*));
	for (int i = 0; i < r1; i++) {
		mat1[i] = malloc(c1 * sizeof(int));
		mat1[i] = (int *) matrices[matIndex1]->mat[i];
	}
	mat2 = malloc(r2 * sizeof(int*));
	for (int i = 0; i < r2; i++) {
		mat2[i] = malloc(c2 * sizeof(int));
		mat2[i] = (int *) matrices[matIndex2]->mat[i];
	}
}

void initializeOutputMat() {
	for (int i = 0; i < r3; ++i) {
		for (int j = 0; j < c3; ++j) {
			mat[i][j] = 0;
		}
	}
}


void destroyMethodsMats() {
	printf("start destroyMethodsMats\n");
	for (int i = 0; i < r1; i++) {
		free(mat1[i]);
	}
	free(mat1);
	for (int i = 0; i < r2; i++) {
		free(mat2[i]);
	}
	free(mat2);
	printf("destroyed destroyMethodsMats\n");
}

void *calculateRowOutput(void *row1) {
	int i1 = (int) row1;
	for (int j2 = 0; j2 < c2; ++j2) {
		for (int j1 = 0; j1 < c1; ++j1) {
			mat[i1][j2] += mat1[i1][j1] * mat2[j1][j2];
		}
	}
	pthread_exit(NULL);
}

void *calculateElementOutput(void *pair) {
	struct pair *p;
	p = (struct pair*) pair;
	int i1 = p->r;
	int j2 = p->c;

	for (int j1 = 0; j1 < c1; ++j1) {
		mat[i1][j2] += mat1[i1][j1] * mat2[j1][j2];
	}
	pthread_exit(NULL);
}

void naive_method(int matOutpuMat){
	int i, j, k;
	struct timeval stop, start;
	//start checking time
	gettimeofday(&start, NULL);
	for (i = 0; i < r1; i++) {
		for(j = 0; j < c2; j++){
			for(k = 0; k < r2; k++){
				int temp = mat1[i][k] * mat2[k][j];
			}
		}
	}
	//end checking time
	gettimeofday(&stop, NULL);
	//print threads excuting time.
	green();
	printf("naive method Time >> %lu Seconds,  %lu Microseconds\n",
			stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec);
	reset();
}


void method1(int matOutpuMat) {
	int i, j;
	struct timeval stop, start;
	//start checking time
	gettimeofday(&start, NULL);
	pthread_t threads[r3];
	for (i = 0; i < r3; i++) {
		if (pthread_create(&threads[i], NULL, calculateRowOutput, (void *) i)) {
			printf("Can not create a thread\n");
			exit(1);
		}
	}
	for (i = 0; i < r3; i++) {
		pthread_join(threads[i], NULL);
	}
	//end checking time
	gettimeofday(&stop, NULL);
	//print threads excuting time.
	green();
	printf("Method 1 Time >> %lu Seconds,  %lu Microseconds\n",
			stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec);
	reset();

	addMatrix(r3, c3, mat, matOutpuMat);
}

void method2(int matOutpuMat) {
	int i, j;
	struct timeval stop, start;
	//start checking time
	gettimeofday(&start, NULL);
	pthread_t threads[r3 * c3];
	for (i = 0; i < r3; i++) {
		for (j = 0; j < c3; j++) {
			struct pair *p;
			p = (struct pair*) malloc(sizeof(struct pair));
			p->r = i;
			p->c = j;
			if (pthread_create(&threads[(i * c3) + j], NULL,
					calculateElementOutput, (void *) p)) {
				printf("Can not create a thread\n");
				exit(1);
			}
		}
	}
	for (i = 0; i < r3; i++) {
		for (j = 0; j < c3; j++) {
			pthread_join(threads[(i * c3) + j], NULL);
		}
	}
	//end checking time
	gettimeofday(&stop, NULL);
	//print threads excuting time.
	green();
	printf("Method 2 Time >> %lu Seconds,  %lu Microseconds\n",
			stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec);
	reset();
	addMatrix(r3, c3, mat, matOutpuMat);
}

//if numOfMethods = 0 runs all availabe methods.
void runMethod(int matInputIndex1, int matInputIndex2, int matOutputIndex, int numOfMethods) {
	initializeMethodsMats(matInputIndex1,matInputIndex2);
	initializeOutputMat();
	switch (numOfMethods) {
	case 0:
		method1(matOutputIndex);
		initializeOutputMat();
		method2(matOutputIndex);
		initializeOutputMat();
		naive_method(matOutputIndex);
		break;
	case 1:
		method1(matOutputIndex);
		break;
	case 2:
		method2(matOutputIndex);
		break;
	default:
		printf("Not correct number of methods is selected.");
		break;
	}
}
