#include "variables.h"
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_HASHTABLE_LENGTH 65536
#define MAX_PATH_LENGTH 1024

char *PATH, *HOME;
char FILE_DIR[1024];

// this functions used initially to set our variables.
void set_environment_vars() {
	PATH = getenv("PATH");
	HOME = getenv("HOME");
	getcwd(FILE_DIR, 1024);
	set_variable("PATH", PATH);
	set_variable("HOME", HOME);
	set_variable("FILE_DIR", FILE_DIR);
}

char* get_path() {
	return PATH;
}
char* get_home() {
	return HOME;
}
char* get_file_dir() {
	return FILE_DIR;
}

void set_path(char* new_path) {
	PATH = new_path;
	set_variable("PATH", PATH);
}

void set_home(char* new_home) {
	HOME = new_home;
	set_variable("HOME", HOME);
}

void set_file_dir(char new_file_dir[]) {
	memset(FILE_DIR, 0, 1024);
	strcat(FILE_DIR, new_file_dir);
	set_variable("FILE_DIR", FILE_DIR);
}

hashtable_t *hashtable;

void initialize_ht() {
	hashtable = ht_create( MAX_HASHTABLE_LENGTH);
}

char* lookup_variable(char* key) {
	return ht_get(hashtable, key);
}

void set_variable(char* key, char* value) {
	ht_set(hashtable, key, value);
}
