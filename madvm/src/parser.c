// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// parser.h: Parse input string to program

#include <stdlib.h>

#include "parser.h"
#include "madlib.h"

#define STACK_INITIAL_SIZE 256
#define STACK_GROW_SIZE 4

void parse_tokens(token_vector_t *tokens, function_t *function) {
    // stack vector to keep track of loops
    size_t * loop_stack = calloc(STACK_INITIAL_SIZE, sizeof(size_t));
    size_t loop_stack_size = STACK_INITIAL_SIZE;
    size_t loop_stack_count = 0;

    for (size_t i = 0; i < tokens->count; i++) {
        switch (tokens->tokens[i]) {
            case token_pointer_next:
                function_omit_move_next(function);
                break;
            case token_pointer_prev:
                function_omit_move_prev(function);
                break;
            case token_increment:
                function_omit_increment(function);
                break;
            case token_decrement:
                function_omit_decrement(function);
                break;
            case token_start_loop:
                if (loop_stack_count >= loop_stack_size) {
                    size_t new_size = loop_stack_size + STACK_GROW_SIZE;
                    size_t total_bytes = new_size * sizeof(size_t);
                    loop_stack = realloc(loop_stack, total_bytes);
                    loop_stack_size = new_size;
                }
                loop_stack[loop_stack_count++] = function->count;
                break;
            case token_end_loop:
                if (loop_stack_count > 0) {
                    function_omit_jump(function, loop_stack[--loop_stack_count]);
                }
                else {
                    // TODO: Error
                    abort();
                }
                break;
            case token_print:
                function_omit_calli(function, MADLIB_FUNCTION_PUT);
                break;
            case token_read:
                function_omit_calli(function, MADLIB_FUNCTION_GET);
                break;
        }
    }

    free(loop_stack);

    if (loop_stack_count > 0) {
        // TODO: Error
        abort();
    }
}
