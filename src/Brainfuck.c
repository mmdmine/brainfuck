// Simple brainfuck interpreter
// Copyright 2020 (C) by Mohammad Amin Mollazadeh

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<limits.h>

#include "Brainfuck.h"

cell memory[256];
char* ip;
cell* ptr;

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

char* interpret()
{
	while (*ip != 0)
	{
		switch (*ip)
		{
		case '>':
			if (ptr < memory+255)
			{
				++ptr;
			}
			else
			{
				printf("Out of cells.\n");
				exit(1);
			}
			break;
		case '<':
			if (ptr > memory)
			{
				--ptr;
			}
			else
			{
				printf("Out of cells.\n");
				exit(1);
			}
			break;
		case '+':
			if (*ptr < UCHAR_MAX)
			{
				(*ptr)++;
			}
			else
			{
				printf("Cell reached maximum.\n");
				exit(1);
			}
			break;
		case '-':
			if (*ptr > 0)
			{
				(*ptr)--;
			}
			else
			{
				printf("Cell reached minimum.\n");
				exit(1);
			}
			break;
		case '.':
			putc(*ptr, stdout);
			break;
		case ',':
			*ptr = (cell)getc(stdin);
			break;
		case '[':
			ip++;
			char *loop_start = ip;
			while(*ptr)
			{
				ip = loop_start;
				interpret();
			}
			while (*ip != ']')
			{
				ip++;
				if (*ip == 0)
				{
					printf("Unexpected end of program.\n");
					exit(1);
				}
			}
			break;
		case ']':
			return ip;
		default:
			// ignore
			break;
		}
		ip++;
	}
	return ip;
}

int main(const int argc, char** args)
{
	if (argc > 1)
	{
		char* program = read_file(args[1]);
		ip = program;
		ptr = memory;
		interpret();
		free(program);
		return 0;
	}

	printf("Mad Brainfuck Interpreter\n");
	printf("Copyright (C) 2020 By Mohammad Amin Mollazadeh\n\n");
	printf("Usage: %s <file name>\n", args[0]);
	return 1;
}
