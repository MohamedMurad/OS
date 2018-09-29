#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "additional_functions.h"

void red() {
	printf("\033[1;31m");
}

void reset() {
	printf("\033[0;0m");
}

void print_argumants(char **args) {
	int i = 0;
	while (args[i] != NULL) {
		printf("%s\n", args[i]);
		i++;
	}
}

int get_size(char **args) {
	int i = 0;
	while (args[i] != NULL) {
		i++;
	}
	return i;
}

int find_length(char *input) {
	int length = 0;
	while (input != NULL && input[length] != '\0')  //  remove ;
	{
		length++;
	}
	return length;
}

char *trim(char *str) {
	size_t len = 0;
	char *frontp = str;
	char *endp = NULL;
	if (str == NULL) {
		return NULL;
	}
	if (str[0] == '\0') {
		return str;
	}
	len = strlen(str);
	endp = str + len;
	while (isspace((unsigned char) *frontp)) {
		++frontp;
	}
	if (endp != frontp) {
		while (isspace((unsigned char) *(--endp)) && endp != frontp) {
		}
	}
	if (str + len - 1 != endp)
		*(endp + 1) = '\0';
	else if (frontp != str && endp == frontp)
		*str = '\0';
	endp = str;
	if (frontp != str) {
		while (*frontp) {
			*endp++ = *frontp++;
		}
		*endp = '\0';
	}
	return str;
}
