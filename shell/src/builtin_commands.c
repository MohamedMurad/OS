#include "builtin_commands.h"
#include "variables.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 513

char *builtin_str[] = { "cd", "help", "exit", "printenv" };

void cd(char** args) {
	if (args[1] == NULL) {
		printf("directory not specified\n");
	} else {
		char path_edited[MAX_LINE_LENGTH] = "";
		char *path = args[1];
		int path_index = 0, path_edited_index = 0;
		while (path[path_index] != '\0') {
			while (path[path_index] != '\0' && path[path_index] != '$') {
				path_edited[path_edited_index++] = path[path_index++];
			}
			char var[MAX_LINE_LENGTH] = "";
			int j = 0;
			path_index++;

			while (isalpha(path[path_index]) || isdigit(path[path_index])
					|| path[path_index] == '_') {
				var[j++] = path[path_index++];
			}
			// add the value of var from hashtable in its position.
			if (var[0] != '\0') {
				char *value;
				value = lookup_variable(var);
				if (value != NULL) {
					for (j = 0; value[j] != '\0'; j++) {
						path_edited[path_edited_index++] = value[j];
					}
				}
			}
		}
		path_edited[path_edited_index++] = '\0';

		if (path_edited[0] == '~') {
			char new_path[MAX_LINE_LENGTH];
			memset(new_path, 0, MAX_LINE_LENGTH);
			if (path_edited[1] == '\0' || path_edited[1] == NULL) {
				args[1] = get_home();
			} else {
				path_edited[0] = '/';
				strcat(new_path, "/home");
				strcat(new_path, path_edited);
				args[1] = new_path;
			}
		} else {
			args[1] = path_edited;
		}
		if (chdir(args[1]) != 0) {
			perror("error");
		}
	}
}

void echo(char **args) {
	int i = 1, new_i = 0;
	char new_line[MAX_LINE_LENGTH] = "";
	while (args[i] != NULL) {
		char *argv = args[i++];
		int k = 0;
		while (argv[k] != '\0') {

			while (argv[k] != '\0' && argv[k] != '$') {
				new_line[new_i++] = argv[k++];
			}

			char var[MAX_LINE_LENGTH] = "";
			int j = 0;
			k++;

			while (isalpha(argv[k]) || isdigit(argv[k]) || argv[k] == '_') {
				var[j++] = argv[k++];
			}
			// add the value of var from hashtable in its position.
			if (var[0] != '\0') {
				char *value;
				value = lookup_variable(var);

				if (value != NULL) {
					for (j = 0; value[j] != '\0'; j++) {
						new_line[new_i++] = value[j];
					}
				}
			}
		}
		new_line[new_i++] = ' ';
	}
	printf("%s \n", new_line);
}

void help(char** args) {
	int i;
	printf("\n\nMohamed Murads's Shell, CSED19\n");
	int n = sizeof(builtin_str) / sizeof(char *);
	printf("The following are built in:\n");
	for (i = 0; i < n; i++) {
		printf("  %s\n", builtin_str[i]);
	}
	printf("  echo\n");
	printf("  history\n");
	printf("Use the man command for extra information on programs.\n\n");
}

void exit_shell(char** args) {
	exit(0);
}

void printenv(char** args) {
	printf("PATH=%s\n", get_path());
	printf("HOME=%s\n", get_home());
	printf("SHELL_DIR=%s\n", get_file_dir());
}

int (*builtin_func[])(char **) = {
	&cd,
	&help,
	&exit_shell,
	&printenv
};

int excute_builtin_command(char** args) {

	int n = sizeof(builtin_str) / sizeof(char *);
	for (int i = 0; i < n; i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			(*builtin_func[i])(args);
			return 1;
		}
	}
	if (strcmp(args[0], "echo") == 0) {
		echo(args);
		return 1;
	} else if (strcmp(args[0], "history") == 0 && args[1] == NULL) {
		read_from_history();
		return 1;
	}
	return -1;
}
