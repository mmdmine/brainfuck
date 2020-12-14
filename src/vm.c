// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.c: Virtual Machine Implementation

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#include "vm.h"
#include "madlib.h"

cell memory[256];
char* ip;
cell* ptr;

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
                    // TODO: Set error flag and return
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
                    // TODO: Set error flag and return
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
                put(*ptr);
                break;
            case ',':
                *ptr = get();
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

void run(program program) {
    ip = program.raw;
    ptr = memory;
    interpret();
}
