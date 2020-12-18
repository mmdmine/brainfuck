// Mad Brainfuck Interpreter
// By @the_madamin

// parser.h: Parse tokens and omit opcodes to functions

#include <stdlib.h>

#include "parser.h"
#include "madlib.h"

// Stack Frame vector
//

// Initial size of loop stack vector
#define STACK_INITIAL_SIZE 256
// Count of new entries to be allocated when vector needs to grow
#define STACK_GROW_SIZE 4

struct {
    size_t * values;
    size_t count;
    size_t size;
} stack_frame;

void push_to_stack(size_t value) {
    if (stack_frame.count >= stack_frame.size) {
        size_t new_size = stack_frame.size + STACK_GROW_SIZE;
        size_t total_bytes = new_size * sizeof(size_t);
        stack_frame.values = realloc(stack_frame.values, total_bytes);
        stack_frame.size = new_size;
    }
    stack_frame.values[stack_frame.count++] = value;
}

size_t pop_from_stack() {
    if (stack_frame.count > 0) {
        return stack_frame.values[--stack_frame.count];
    }
    else {
        // TODO: Error
        abort();
    }
}

void parse_tokens(token_vector_t *tokens, function_t *function) {
    // Initialize stack
    stack_frame.values = calloc(STACK_INITIAL_SIZE, sizeof(size_t));
    stack_frame.size = STACK_INITIAL_SIZE;
    stack_frame.count = 0;

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
            case token_open_bracket:
                push_to_stack(function->count);
                break;
            case token_close_bracket:
                function_omit_jump(function, pop_from_stack());
                break;
            case token_put_char:
                function_omit_calli(function, MADLIB_FUNCTION_PUT);
                break;
            case token_get_char:
                function_omit_calli(function, MADLIB_FUNCTION_GET);
                break;
        }
    }

    free(stack_frame.values);

    // One or more ']' are missing
    if (stack_frame.count > 0) {
        // TODO: Error
        abort();
    }
}
