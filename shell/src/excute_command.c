#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "excute_command.h"
#include "builtin_commands.h"
#include "variables.h"

#define MAX_LINE_LENGTH 513

typedef enum {
	false = 0, true = 1
} bool;

bool background = false;

// this functions used to check if command should run on background.
void check_background(char **args) {
	int n = get_size(args);
	if (strcmp(args[n - 1], "&") == 0) {
		background = true;
	} else {
		background = false;
	}
}

// this function used to remove "&" symbol from the argv.
void reset_args_for_background(bool background, char **args) {
	if (background) {
		int n = get_size(args);
		args[n - 1] = NULL;
	}
}

int excute_command(char **args) {
	int i;
	if (args[0] == NULL) {
		// An empty command.
		return 1;
	}
	check_background(args);
	reset_args_for_background(background, args);
	pid_t pid;
	pid = fork();
	int status;
	//check here for builtin functions to excute.
	if (pid == 0) {
		if (excute_builtin_command(args) == -1) {
			if (excute(args) == -1) {
				//check for variables and set them.
				set_vars(args);
			}
		}
	} else {
		// Parent
		if (!background) {
			/*If not running in background..wait for process to finish*/
			waitpid(pid, &status, WUNTRACED);
		} else {
			printf("%ld Started..\n", (long) getpid());
			return 1;
		}
	}
	write_in_log_file();
	return 1;
}

void set_vars(char **args) {
	int i = 0;
	while (args[i] != NULL) {
		int j = 0, k = 0;
		char key[MAX_LINE_LENGTH];
		char value[MAX_LINE_LENGTH];
		bool is_var = false;
		while (args[i][k] != '\0') {
			is_var = false;
			while (args[i][k] != '\0' && args[i][k] != '=') {
				key[j++] = args[i][k++];
			}
			key[j] = '\0';
			j = 0;
			if (args[i][k] == '=') {
				k++;
				if (args[i][k] == '"') {
					k++;
					while (args[i][k] != '"') {
						if (args[i][k + 1] == '\0') {
							perror("end of double quotation is missing");
							exit(EXIT_FAILURE);
						}
						value[j++] = args[i][k++];
					}
					k++;
				} else {
					while (args[i][k] != '\0') {
						if (args[i][k] == '$') {

							char var[MAX_LINE_LENGTH] = "";
							int var_index = 0;
							k++;

							while (isalpha(args[i][k]) || isdigit(args[i][k])
									|| args[i][k] == '_') {
								var[var_index++] = args[i][k++];
							}
							// add the value of var from hashtable in its position.
							if (var[0] != '\0') {
								char *val;
								val = lookup_variable(var);

								if (value != NULL) {
									for (int m = 0; val[m] != '\0'; m++) {
										value[j++] = val[m];
									}
								}
							}

						} else {
							value[j++] = args[i][k++];
						}
					}
				}
				value[j] = '\0';
				is_var = true;
				if (strcmp(key, "PATH") == 0) {
					set_path(value);
				} else if (strcmp(key, "HOME") == 0) {
					set_home(value);
				} else if (strcmp(key, "FILE_DIR") == 0) {
					set_home(value);
				} else {
					set_variable(key, value);
				}
			}
			if (!is_var) {
				perror(key);
			}
		}
		i++;
	}
}

int excute(char **args) {
	char *path = malloc(513 * sizeof(char*));
	int j = 0, k = 0;

	char* p = get_path();

	while (p[k] != '\0') {
		memset(path, 0, 513);
		j = 0;
		execv(args[0], args);
		while (p[k] != ':' && p[k] != '\0') {
			path[j++] = p[k++];
		}
		k++;
		strcat(path, "/");
		strcat(path, args[0]);
		execv(path, args);
	}
	free(path);
	return -1;
}
