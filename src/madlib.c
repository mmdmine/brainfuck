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
    register_function(MADLIB_FUNCTION_PUT, put);
    register_function(MADLIB_FUNCTION_GET, get);
}
