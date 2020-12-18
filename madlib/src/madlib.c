// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// madlib.c: MadBf Standard Library

#include <stdio.h>

#include "madlib.h"

void put(machine_state *state) {
    putchar(*(state->memory_pointer));
}

void get(machine_state *state) {
    *(state->memory_pointer) = getchar();
}

void madlib_register() {
    vm_register_native_function(MADLIB_FUNCTION_PUT, put);
    vm_register_native_function(MADLIB_FUNCTION_GET, get);
}
