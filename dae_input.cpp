#include <stdio.h>
#include <stdlib.h>

#include "dae_input.h"

/**
 * Gets a tag <...> from a file.
 * Returns null if there's any problem, including the next thing in the file
 * not being a tag.
 */
char *getTag(FILE *input_file)
{
	int buffer_size = 1024;
	char *b, *s;
	int i;
	char c;
	
	c = getc(input_file);
	ungetc(c, input_file);
	if (c != '<') {
		return NULL;
	}
	
	i = 0;
	b = (char *)malloc(buffer_size);
	if (!b) {
		return NULL;
	}
	while ((c = getc(input_file)) != EOF) {
		if (i >= buffer_size) {
			buffer_size += 1024;
			b = (char *)realloc(b, buffer_size);
			if (!b) {
				return NULL;
			}
		}
		
		b[i] = c;
		i++;
		
		if (c == '>') {
			int j;
			
			s = (char *)malloc(i+1);
			if (!s) {
				return NULL;
			}
			for (j = 0; j < i; j++) {
				s[j] = b[j];
			}
			s[i] = 0;
			free(b);
			return s;
		}
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: dae_input <filename>");
		return 1;
	}
	
	FILE *input_file = fopen(argv[1], "r");
	if (!input_file) {
		fprintf(stderr, "Could not open file: %s\n", argv[1]);
		return 1;
	}
	
	char *s = getTag(input_file);
	printf("%s", s);
	
	fclose(input_file);
}

/**
 * Constructs a DAETree from the file, whose filename is given.
 */
DAETree::DAETree(char *filename)
{
	FILE *input_file = fopen(filename, "r");
	if (!input_file) {
		fprintf(stderr, "Could not open file: %s\n", filename);
		return;
	}
	
	fclose(input_file);
}