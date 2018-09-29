#ifndef BUILTIN_COMMANDS_H_   /* Include guard */
#define BUILTIN_COMMANDS_H_

/* 
 -
 */
void cd(char** args);

/*

 */
void echo(char** args);

/*
 - This function should be responsible for implementing the "help" shell command
 */
void help(char** args);

/*
 - This function should be responsible for implementing the "exit" shell command
 */
void exit_shell(char** args);

/*
 - This function should be responsible for implementing the builtin command
 - returns -1 if it's not a builting command
 */
int excute_builtin_command(char** args);

#endif // BUILTIN_COMMANDS_H_
