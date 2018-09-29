#ifndef ADDITIONAL_FUNCTIONS_H_   /* Include guard */
#define ADDITIONAL_FUNCTIONS_H_

/* 
 - This function used to print contents of all passed list of arguments.
 */
void print_argumants(char **args);

/* 
 - This function used to find numbers of arguments.
 */
int get_size(char **args);

/* 
 - This function should get the length of an input.
 */
int find_length(char *input);

/* 
 - This function used to remove leading and trailing spaces.
 */
char *trim(char *str);

/*
 - red ANSI color code.
 */
void red();

/*
 - default ANSI color code.
 */
void reset();

#endif // ADDITIONAL_FUNCTIONS_H_
