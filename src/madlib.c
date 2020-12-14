// Mad Brainfuck Standard Library
// Copyright (C) 2020 Mohammad Amin Mollazadeh

#include <stdio.h>

#include "madlib.h"

void register_library() {
    register_function("put", put);
    register_function("get", get);
}

void put(machine_state *state) {
    putchar(*(state->memory_pointer));
}

void get(machine_state *state) {
    *(state->memory_pointer) = getchar();
}
