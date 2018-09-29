#ifndef EXCUTE_COMMAND_H   /* Include guard */
#define EXCUTE_COMMAND_H

/* 
 - This function should be responsible for implementing the "cd" shell command
 */
int excute_command(char **args);
void set_vars(char **args);
int excute(char **args);

#endif // EXCUTE_COMMAND_H
