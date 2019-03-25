#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>


char* cipher_with_key(char* message, char* key);
char* cipher_with_key(char* message, char* key);
char* concat(char* s1, char* s2);
char* uncipher(char* s1, char* s2);
void print_usage(void);
char* init_alphabet_array(void);
char* get_message(FILE* file);
int get_filesize(FILE* file);

char* action; 
char* to_open;
char* key;
char* message;
FILE* file;
int length;
char* encoded;

