// Mad Brainfuck Interpreter
// By @the_madamin

// function.c: Function manipulation functions implementation

#include <stdlib.h>
#include <string.h>
#include <assert.h>

// in Windows, we should use ISO C _strdup instead of POSIX strdup
#ifdef WIN32
#define strdup _strdup
#endif

#include "function.h"

function_t *function_new(size_t initial_size) {
    assert(initial_size != 0);

    function_t *result = malloc(sizeof(struct function));
    result->opcodes = calloc(initial_size, sizeof(opcode_t));

    result->size = initial_size;
    result->count = 0;

    return result;
}

void function_free(function_t *self) {
    // free strings used in calli opcodes
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
    // grow vector when it reaches the bound
    if (self->count >= self->size) {
        function_grow(self, FUNCTION_GROW_SIZE);
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

size_t function_omit_calli(function_t *self, char * target) {
    opcode_t opcode;
    opcode.type = opcode_type_calli;
    opcode.data.calli_data = strdup(target);

    return function_omit(self, opcode);
}

size_t function_omit_jump(function_t *self, size_t target) {
    opcode_t opcode;
    opcode.type = opcode_type_ifjump;
    opcode.data.jump_data = target;

    return function_omit(self, opcode);
}
