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

machine_state state;

char* interpret()
{
    while (*ip != 0)
    {
        switch (*ip)
        {
            case '>':
                if (state.memory_pointer < memory+255)
                {
                    ++(state.memory_pointer);
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Out of cells.\n");
                    exit(1);
                }
                break;
            case '<':
                if (state.memory_pointer > memory)
                {
                    --(state.memory_pointer);
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Out of cells.\n");
                    exit(1);
                }
                break;
            case '+':
                if (*(state.memory_pointer) < UCHAR_MAX)
                {
                    (*(state.memory_pointer))++;
                }
                else
                {
                    printf("Cell reached maximum.\n");
                    exit(1);
                }
                break;
            case '-':
                if (*(state.memory_pointer) > 0)
                {
                    (*(state.memory_pointer))--;
                }
                else
                {
                    printf("Cell reached minimum.\n");
                    exit(1);
                }
                break;
            case '.':
                put(*(state.memory_pointer));
                break;
            case ',':
                *(state.memory_pointer) = get();
                break;
            case '[':
                ip++;
                char *loop_start = ip;
                while(*(state.memory_pointer))
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
    state.memory_pointer = memory;
    interpret();
}
