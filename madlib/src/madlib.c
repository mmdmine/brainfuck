// Mad Brainfuck Interpreter
// By @the_madamin

// madlib.c: Standard Library Implementation for Mad Brainfuck

#include <stdio.h>

#include "madlib.h"
#include "vm.h"

void put(machine_state *state) {
    putchar(state->memory[state->memory_position]);
}

void get(machine_state *state) {
    state->memory[state->memory_position] = getchar();
}

void madlib_register() {
    vm_register_native_function(MADLIB_FUNCTION_PUT, put);
    vm_register_native_function(MADLIB_FUNCTION_GET, get);
}
