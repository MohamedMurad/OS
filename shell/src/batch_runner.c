#include <string.h>
#include <stdio.h>

#include "variables.h"
#include "batch_runner.h"
#include "excute_command.h"
#include "command_parser.h"
#include "additional_functions.h"

#define MAX_LINE_LENGTH 513

void run_batch(char *path) {
	FILE *f;
	f = fopen(path, "r");
	int bufsize = MAX_LINE_LENGTH, position = 0;

	if (f != NULL) {
		printf("\n");
		char* line = malloc(MAX_LINE_LENGTH * sizeof(char*));
		memset(line, 0, MAX_LINE_LENGTH);
		while (fgets(line, MAX_LINE_LENGTH, f) != NULL) /* read a line */
		{
			char** args;
			args = parse_command(line);
			red();
			printf("Shell> ");
			reset();
			fputs(line, stdout); /* write the line */
			//excute_command(args);
			memset(line, 0, MAX_LINE_LENGTH);
		}
		free(line);
		fclose(f);
	} else {
		perror(path); /* why didn't the file open? */
	}
	printf("OUT OF BATCH\n");
}
