#include <stdio.h>
#include <string.h>

#include "variables.h"

#define MAX_LINE_LENGTH 513

void read_from_history() {
	FILE *f;
	char* path;
	asprintf(&path, "%s%s", get_file_dir(), "/history/history.txt");
	f = fopen(path, "r");
	int i = 1;
	printf("\n");
	if (f != NULL) {
		char line[MAX_LINE_LENGTH];
		while (fgets(line, sizeof line, f) != NULL) /* read a line */
		{
			printf(" %d ", i);
			fputs(line, stdout); /* write the line */
			i++;
		}
		fclose(f);
	} else {
		perror("history.txt"); /* why didn't the file open? */
	}
}
