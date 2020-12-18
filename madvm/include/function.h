// Mad Brainfuck Interpreter
// By @the_madamin

// function.h: Runtime Function Definition

#pragma once

#include <stddef.h>

#include "opcode.h"

// Count of new entries to be allocated when vector needs to grow
#define FUNCTION_GROW_SIZE 4

// Defining function vector type
//

typedef struct function function_t;

struct function {
    opcode_t *opcodes;
    size_t size;
    size_t count;
};

// Function manipulation functions
//

// allocate memory for new function
// initial_size: initial count of entries for new vector
function_t *function_new(size_t initial_size);
// free resources that's used by function
void function_free(function_t *self);
// grow size of opcodes vector
void function_grow(function_t *self, size_t count);
// omit a opcode to function and return its index
// function grows by FUNCTION_GROW_SIZE automatically when it reaches to bounds
size_t function_omit(function_t *self, opcode_t opcode);
// create a new increment opcode and omit it to function
size_t function_omit_increment(function_t *self);
// create a new decrement opcode and omit it to function
size_t function_omit_decrement(function_t *self);
// create a new move_next opcode and omit it to function
size_t function_omit_move_next(function_t *self);
// create a new move_prev opcode and omit it to function
size_t function_omit_move_prev(function_t *self);

// create a new jump opcode and omit it to function
// target: position to jump
size_t function_omit_jump(function_t *self, size_t target);

// create a new calli opcode and omit it to function
// target: function to be called, it will be copied
size_t function_omit_calli(function_t *self, char * target);
