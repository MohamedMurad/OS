#include <string.h>
#include <stdio.h>

#include <stdio.h>
#include "variables.h"

void write_in_history(char* line) {
	FILE *f;
	char* path;
	asprintf(&path, "%s%s", get_file_dir(), "/history/history.txt");
	f = fopen(path, "a+");
	if (f == NULL)
		exit(-1);
	fprintf(f, "%s\n", line);
	fclose(f);
}

void write_in_log_file() {
	FILE *f;
	char* path;
	asprintf(&path, "%s%s", get_file_dir(), "/log/log.txt");
	f = fopen(path, "a+");
	if (f == NULL)
		exit(-1);
	fprintf(f, "child process was terminated..\n");
	fclose(f);
}
