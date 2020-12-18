// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.c: Mad Brainfuck's VM and Interpreter

#include<stdio.h>
#include<limits.h>

#include "vm.h"
#include "dictionary.h"

cell memory[MEMORY_SIZE];

machine_state state;
dictionary_t *native_functions;

void vm_init() {
    state.memory_pointer = memory;
    native_functions = dictionary_new(DICTIONARY_GROW_SIZE);
}

void vm_free() {
    dictionary_free(native_functions);
}

void vm_register_native_function(char *function_name, void *function_address) {
    dictionary_append(native_functions, function_name, function_address);
}

void vm_run_native_function(char *function_name) {
    void (*func)(machine_state*) = dictionary_lookup(native_functions, function_name);
    if (func == NULL) {
        // TODO: error
        return;
    }
    (*func)(&state);
}

void vm_execute(function_t *function) {
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
                    printf("Cell reached to maximum value.\n");
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
                    printf("Cell reached to minimum value.\n");
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
                    printf("Cell pointer reached to end of memory.\n");
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
                    printf("Cell pointer reached to start of memory.\n");
                    return;
                }
                break;
            case opcode_type_calli:
                vm_run_native_function(current_opcode->data.calli_data);
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
