// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.c: Virtual Machine Implementation

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#include "vm.h"
#include "dictionary.h"

cell memory[256];

char* ip;

machine_state state;
dictionary functions_registry;

void vm_init() {
    state.memory_pointer = memory;
    functions_registry = dictionary_new(8); // TODO: use 8 for now
}

void vm_free() {
    dictionary_free(functions_registry);
}

void register_function(const char *function_name, void *function_address) {
    dictionary_add(functions_registry, function_name, function_address);
}

void call_function(char *function_name) {
    void (*func)(machine_state*) = dictionary_lookup(functions_registry, function_name);
    if (func == NULL) {
        // TODO: error
        return;
    }
    (*func)(&state);
}

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
                call_function("put");
                break;
            case ',':
                call_function("get");
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
    interpret();
}
