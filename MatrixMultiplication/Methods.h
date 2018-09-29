/*
 * Methods.h
 *
 *  Created on: Oct 19, 2017
 *      Author: mohamed
 */

#ifndef METHODS_H_
#define METHODS_H_

/**
 * initialize local matrices to use in computation
 */
void initializeMethodsMats(int matIndex1, int matIndex2);

/**
 * destroy local matrices used in computation
 */
void destroyMethodsMats();

/**
 * run different methods to multiply matrices
 * the first three args are 2 inputs and output indices in out matrices list.
 * numOfMethods runs all methods if it's 0, otherwise it runs the selected method number.
 */
void runMethod(int matIndex1, int matIndex2, int matOutputIndex, int numOfMethods);

#endif /* METHODS_H_ */
