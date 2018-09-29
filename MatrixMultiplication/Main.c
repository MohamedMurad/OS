#include "FileReader.h"
#include "FileWriter.h"
#include "Matrices.h"
#include "Methods.h"
#include "Color.h"

#include <stdio.h>
#include <stdlib.h>

void runner(int argc, char *argv[]){
	//index of the current matrix.
	int matIndex = 0;
	//initialize 2 inputs and 1 output, we can easily extend it.
	initializeMats(3);

	//read first matrix and add it to our list.
	readMatrix(argv[1]);
	addMatrix(getNumOfRow(), getNumOfCol(), getMat(), matIndex);
	matIndex++;

	//read second matrix and add it to our list.
	readMatrix(argv[2]);
	addMatrix(getNumOfRow(), getNumOfCol(), getMat(), matIndex);
	matIndex++;

	printf("first input matrix:\n");
	printMatrix(0);
	printf("second input matrix:\n");
	printMatrix(1);

	//calculate all available methods.
	runMethod(0, 1, 2,0);

	//write results matrix in a file.
	//writeMatrix(argc, 2, argv[3]);

	printf("output matrix:\n");
	printMatrix(2);
}

void deallocation(){
	//deallocation.
	red();
	destroyMats();
	destroyMethodsMats();
	reset();
}

int main(int argc, char *argv[]) {
	//run program.
	runner(argc, argv);
	//deallocate memory.
	deallocation();
	return 0;
}
