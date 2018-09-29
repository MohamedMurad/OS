#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_

/* 
 - This function should be responsible for getting the value of a variable
 - To execute commands, You must always search for the executable files
 in the value returned by lookup_variable("PATH");
 - Your code must be dynamic and can handle any number of variables, However,
 performance is not an issue since in practice we expect low number of variables,
 as a tip: simple array lookup would be fine
 */
char* lookup_variable(char* key);

/*
 - This function should be responsible for setting the value of a variable
 */
void set_variable(char* key, char* value);

/*
 - this function used initially to set environment vars such as PATH, HOME...etc.
 */
void set_environment_vars();

/*
 - this function used to initialize our hashtable which is used for session variables.
 */
void initialize_ht();

/*
 - a getter used to get PATH environment variable.
 */
char* get_path();

/*
 - a getter used to get HOME environment variable.
 */
char* get_home();

/*
 - a getter used to get FILE_DIR environment variable.
 */
char* get_file_dir();

/*
 - a setter used to set FILE_DIR environment variable.
 */
void set_file_dir(char new_file_dir[]);

/*
 - a setter used to set PATH environment variable.
 */
void set_path(char* new_path);

/*
 - a setter used to set HOME environment variable.
 */
void set_home(char* new_home);

#endif // VARIABLES_H_
