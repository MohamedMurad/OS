#include "read.h"
#include <stdio.h>
#include <unistd.h>

char *read_from_terminal(void) {
	char* line = NULL;
	ssize_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return line;
}

