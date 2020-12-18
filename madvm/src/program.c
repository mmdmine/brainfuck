// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// program.c: MadBf Program

#include <stdlib.h>
#include <string.h>

#include "program.h"

program_t *program_new() {
    program_t *result = malloc(sizeof(program_t));
    result->main = NULL;
    return result;
}

void program_free(program_t *self) {
    if (self->main != NULL) {
        free(self->main);
    }
    free(self);
}

function_t *function_new(size_t initial_size) {
    function_t *result = malloc(sizeof(struct function));
    if (initial_size != 0) {
        result->opcodes = calloc(initial_size, sizeof(opcode_t));
    }
    result->size = initial_size;
    result->count = 0;
    return result;
}

void function_free(function_t *self) {
    for (size_t i = 0; i < self->count; i++) {
        if (self->opcodes[i].type == opcode_type_calli) {
            free(self->opcodes[i].data.calli_data);
        }
    }
    free(self->opcodes);
    free(self);
}

void function_grow(function_t *self, size_t count) {
    size_t new_size = self->size + count;
    size_t total_bytes = new_size * sizeof(opcode_t);
    self->opcodes = realloc(self->opcodes, total_bytes);
    self->size = new_size;
}

size_t function_omit(function_t *self, opcode_t opcode) {
    if (self->count >= self->size) {
        function_grow(self, FUNCTION_GROW_STEP);
    }
    self->opcodes[self->count] = opcode;
    return self->count++;
}

#define FUNCTION_OMIT_IMPL(NAME,TYPE) size_t NAME(function_t *self) {\
    opcode_t opcode;\
    opcode.type = TYPE;\
    return function_omit(self, opcode);\
}

FUNCTION_OMIT_IMPL(function_omit_increment, opcode_type_increment)
FUNCTION_OMIT_IMPL(function_omit_decrement, opcode_type_decrement)
FUNCTION_OMIT_IMPL(function_omit_move_next, opcode_type_move_next)
FUNCTION_OMIT_IMPL(function_omit_move_prev, opcode_type_move_prev)

#ifdef WIN32
#define strdup _strdup
#endif

size_t function_omit_calli(function_t *self, char * target) {
    opcode_t opcode;
    opcode.type = opcode_type_calli;
    opcode.data.calli_data = strdup(target);
    return function_omit(self, opcode);
}

size_t function_omit_jump(function_t *self, size_t target) {
    opcode_t opcode;
    opcode.type = opcode_type_jump;
    opcode.data.jump_data = target;
    return function_omit(self, opcode);
}