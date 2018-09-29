#include "command_parser.h"
#include "variables.h"
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 513
#define LSH_TOK_DELIM " \t\r\n\a"

char **parse_command(char* line) {
	const int bufsize = MAXSIZE;
	int line_index = 0, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	while (line[line_index] != '\0' && line[line_index] != NULL) {
		char* token = malloc(bufsize * sizeof(char*));
		int token_index = 0;
		while (line[line_index] != '\0' && line[line_index] != ' '
				&& line[line_index] != '\t' && line[line_index] != '"') {
			token[token_index++] = line[line_index++];
		}

		if (line[line_index] == '"') {
			line_index++;
			while (line[line_index] != '"') {
				if (line[line_index + 1] == '\0') {
					perror("end of double quotation is missing");
					exit(EXIT_FAILURE);
				}
				token[token_index++] = line[line_index++];
			}
			line_index++;
		}
		token[token_index] = '\0';

		while (line[line_index] != '\0'
				&& (line[line_index] == ' ' || line[line_index] == '\t')) {
			line_index++;
		}

		tokens[position++] = token;
	}
	tokens[position] = NULL;
	return tokens;
}
