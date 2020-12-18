// test madvm/src/function.c

#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "function.h"

#define VECTOR_INITIAL_SIZE 4

int main(int argc, char ** argv) {
    // test function_new
    function_t * function = function_new(VECTOR_INITIAL_SIZE);
    assert(function != NULL);
    assert(function->opcodes != NULL);
    assert(function->count == 0);
    assert(function->size == VECTOR_INITIAL_SIZE);

    // test function_omit_* and function_grow
    function_omit_increment(function);
    assert(function->count == 1);
    assert(function->opcodes[0].type == opcode_type_increment);

    function_omit_decrement(function);
    assert(function->count == 2);
    assert(function->opcodes[1].type == opcode_type_decrement);

    function_omit_move_next(function);
    assert(function->count == 3);
    assert(function->opcodes[2].type == opcode_type_move_next);

    function_omit_move_prev(function);
    assert(function->count == 4);
    assert(function->opcodes[3].type == opcode_type_move_prev);

    assert(function->size == VECTOR_INITIAL_SIZE);

    function_omit_jump(function, 1);
    assert(function->size == VECTOR_INITIAL_SIZE + FUNCTION_GROW_SIZE);
    assert(function->count == 5);
    assert(function->opcodes[4].type == opcode_type_ifjump);
    assert(function->opcodes[4].data.jump_data == 1);

    function_omit_calli(function, "test");
    assert(function->count == 6);
    assert(function->opcodes[5].type == opcode_type_calli);
    assert(strcmp(function->opcodes[5].data.calli_data, "test") == 0);

    function_grow(function, 1);
    assert(function->size == VECTOR_INITIAL_SIZE + FUNCTION_GROW_SIZE + 1);

    function_free(function);
}
