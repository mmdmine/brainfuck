// Simple brainfuck interpreter
// Copyright 2020 (C) by Mohammad Amin Mollazadeh

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#include "Brainfuck.h"
#include "vm.h"
#include "parser.h"
#include "madlib.h"

char* read_file(char* file_path)
{
	FILE* file = fopen(file_path, "r");

	if (file == NULL)
	{
		int error = errno;
		printf("Couldn't open file '%s': %s.\n", file_path, strerror(error));
		exit(error);
	}
	
	fseek(file, 0L, SEEK_END);
	long file_size = ftell(file);

	fseek(file, 0L, SEEK_SET);

	char* buffer = calloc(file_size + 1, sizeof(char));

	if (buffer == NULL)
	{
		int error = errno;
		printf("%s.\n", strerror(error));
		exit(error);
	}

	fread(buffer, sizeof(char), file_size, file);

	fclose(file);

	return buffer;
}

int main(const int argc, char** args)
{
	if (argc > 1)
	{
	    vm_init();
	    register_library();

		char* input = read_file(args[1]);
		program input_program = parse(input);

		run(input_program);

		free(input);
		vm_free();

		return 0;
	}

	printf("Mad Brainfuck Interpreter\n");
	printf("Copyright (C) 2020 By Mohammad Amin Mollazadeh\n\n");
	printf("Usage: %s <file name>\n", args[0]);
	return 1;
}
