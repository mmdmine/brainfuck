// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// program.h: MadBf Program

#pragma once

#include <stddef.h>

#define FUNCTION_GROW_STEP 4

typedef struct function function_t;
typedef struct opcode_base opcode_t;

typedef enum {
    opcode_type_increment,
    opcode_type_decrement,
    opcode_type_move_next,
    opcode_type_move_prev,
    // jump to target if current cell is not zero
    opcode_type_jump,
    // call function from library
    opcode_type_calli,
    // TODO: call madbf functions
} opcode_type_t;

typedef union {
    char * calli_data;
    size_t jump_data;
} opcode_data_t;

struct opcode_base {
    opcode_type_t type;
    opcode_data_t data;
};

struct function {
    opcode_t *opcodes;
    size_t size;
    size_t count;
};

struct program {
    function_t *main; // TODO: add support for multiple functions
};

typedef struct program program_t;

program_t *program_new();
void program_free(program_t *self);

function_t *function_new(size_t initial_size);
void function_free(function_t *self);

// omit opcode and return its index
size_t function_omit(function_t *self, opcode_t opcode);

size_t function_omit_increment(function_t *self);
size_t function_omit_decrement(function_t *self);
size_t function_omit_move_next(function_t *self);
size_t function_omit_move_prev(function_t *self);
size_t function_omit_jump(function_t *self, size_t target);
// target will be copied
size_t function_omit_calli(function_t *self, char * target);
