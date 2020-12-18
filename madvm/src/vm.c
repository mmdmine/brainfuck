// Mad Brainfuck Interpreter
// By @the_madamin

// vm.c: Virtual Machine Implementation

#include<stdio.h>

#include "vm.h"
#include "dictionary.h"

machine_state state;

dictionary_t *native_functions;

void vm_init() {
    native_functions = dictionary_new(DICTIONARY_GROW_SIZE);
}

void vm_free() {
    dictionary_free(native_functions);
}

void vm_execute(function_t *function) {
    // TODO: implement jit compiler

    state.function = function;
    state.memory_position = 0;
    state.function_position = 0;

    while (state.function_position < state.function->count) {
        opcode_t *current_opcode = &state.function->opcodes[state.function_position];
        // TODO: replace switch-case with Dictionary to improve performance
        switch (current_opcode->type) {
            case opcode_type_increment:
                if (state.memory[state.memory_position] < CELL_MAX)
                {
                    state.memory[state.memory_position]++;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Cell reached to maximum value.\n");
                    return;
                }
                break;
            case opcode_type_decrement:
                if (state.memory[state.memory_position] > CELL_MIN)
                {
                    state.memory[state.memory_position]--;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Cell reached to minimum value.\n");
                    return;
                }
                break;
            case opcode_type_move_next:
                if (state.memory_position < MEMORY_SIZE)
                {
                    state.memory_position++;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Cell pointer reached to end of memory.\n");
                    return;
                }
                break;
            case opcode_type_move_prev:
                if (state.memory_position > 0)
                {
                    state.memory_position--;
                }
                else
                {
                    // TODO: Set error flag and return
                    printf("Cell pointer reached to start of memory.\n");
                    return;
                }
                break;
            case opcode_type_calli:
                vm_execute_native_function(current_opcode->data.calli_data);
                break;
            case opcode_type_ifjump:
                if (state.memory[state.memory_position] != 0) {
                    state.function_position = current_opcode->data.jump_data;
                }
                break;
            default:
                // TODO: Set error flag and return
                printf("Invalid Opcode.\n");
                return;
        }

        // if program_pointer is not changed, then move program_pointer to next
        if (&state.function->opcodes[state.function_position] == current_opcode) {
            state.function_position++;
        }
    }
}

void vm_register_native_function(char *function_name, void *function_address) {
    dictionary_append(native_functions, function_name, function_address);
}

void vm_execute_native_function(char *function_name) {
    void (*func)(machine_state*) = dictionary_lookup(native_functions, function_name);
    if (func == NULL) {
        // TODO: error
        return;
    }
    (*func)(&state);
}
