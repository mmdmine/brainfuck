// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.c: Mad Brainfuck's VM and Interpreter

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#include "vm.h"
#include "dictionary.h"

cell memory[MEMORY_SIZE];

char* ip;

machine_state state;
dictionary_t *native_functions;

void vm_init() {
    state.memory_pointer = memory;
    native_functions = dictionary_new(DICTIONARY_GROW_SIZE);
}

void vm_free() {
    dictionary_free(native_functions);
}

void register_function(const char *function_name, void *function_address) {
    dictionary_append(native_functions, function_name, function_address);
}

void call_function(char *function_name) {
    void (*func)(machine_state*) = dictionary_lookup(native_functions, function_name);
    if (func == NULL) {
        // TODO: error
        return;
    }
    (*func)(&state);
}

void vm_execute(function_p function) {
    // TODO: implement jit compiler
    state.program_position = 0;
    state.program_pointer = function;

    while (state.program_position < state.program_pointer->count) {
        opcode_t *current_opcode = &state.program_pointer->opcodes[state.program_position];
        switch (current_opcode->type) {
            case opcode_type_increment:
                if (*state.memory_pointer < UCHAR_MAX)
                {
                    (*(state.memory_pointer))++;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Cell value reached maximum.\n");
                    return;
                }
                break;
            case opcode_type_decrement:
                if (*state.memory_pointer > 0)
                {
                    (*(state.memory_pointer))--;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Cell value reached minimum.\n");
                    return;
                }
                break;
            case opcode_type_move_next:
                if (state.memory_pointer < memory + MEMORY_SIZE)
                {
                    (state.memory_pointer)++;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Out of cells.\n");
                    return;
                }
                break;
            case opcode_type_move_prev:
                if (state.memory_pointer > memory)
                {
                    (state.memory_pointer)--;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Out of cells.\n");
                    return;
                }
                break;
            case opcode_type_calli:
                call_function(current_opcode->data.calli_data);
                break;
            case opcode_type_jump:
                if (*state.memory_pointer != 0) {
                    state.program_position = current_opcode->data.jump_data;
                }
                break;
            default:
                // TODO: Set error flag and return
                printf("Invalid Opcode.\n");
                return;
        }

        // if program_pointer is not changed, then move program_pointer to next
        if (&state.program_pointer->opcodes[state.program_position] == current_opcode) {
            state.program_position++;
        }
    }
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
