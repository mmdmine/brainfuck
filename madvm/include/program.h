// Mad Brainfuck Interpreter
// By @the_madamin

// program.h: Runtime Program Definition

#pragma once

#include <stddef.h>

#include "function.h"

// Defining Program type
//

typedef struct program program_t;

struct program {
    // TODO: add support for multiple functions
    function_t *main;
};

// Program manipulation functions
//

program_t *program_new();
void program_free(program_t *self);
