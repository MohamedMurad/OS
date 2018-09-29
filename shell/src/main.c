#include "read.h"
#include "command_parser.h"
#include "variables.h"
#include "additional_functions.h"
#include "builtin_commands.h"
#include "excute_command.h"
#include "file_writer.h"
#include "file_reader.h"
#include "batch_runner.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE_LENGTH 513

int main(int argc, char *argv[]) {

	initialize_ht();
	set_environment_vars();

	if (argc > 2) {
		fputs("too many argumants\n", stderr);
		return -1;
	}

	while (1) {
		red();
		printf("Shell> ");
		reset();
		char* line;
		char** args;
		if (argc > 1) {
			char *path = argv[1];
			run_batch(path);
			exit(-1);
		} else {
			line = read_from_terminal();
			int line_length = find_length(line);
			if (line_length > MAX_LINE_LENGTH) {
				perror(
						"command line should be less than or equal 512 characters.\n");
				continue;
			} else if (find_length(trim(line)) == 0) {
				continue;
			}
			write_in_history(line);
		}
		args = parse_command(line);
		if (args[0][0] == '#') {
			continue;
		}
		excute_command(args);
		free(line);
		free(args);
	}

	return 0;
}
