// Mad Brainfuck Interpreter
// By @the_madamin

// token.h: Token vector definition

#pragma once

#include <stddef.h>
#include <stdio.h>

// Count of entries to be added to token vector when it reaches the bounds
#define TOKEN_VECTOR_GROW_SIZE 4

// Token and Token Vector type definition
//

typedef struct token_vector token_vector_t;

typedef enum {
    token_pointer_next,  // >
    token_pointer_prev,  // <
    token_increment,     // +
    token_decrement,     // -
    token_open_bracket,  // [
    token_close_bracket, // ]
    token_put_char,       // .
    token_get_char,       // ,
    token_call,          // :
    token_fork,          // Y
} token_t;

struct token_vector {
    token_t *tokens;
    size_t count;
    size_t size;
};

// Token Vector Manipulation functions
//

// allocate space for new token vector
// initial_size: entries to be allocated for vector at first
token_vector_t *token_vector_new(size_t initial_size);
// free the resources used by token vector
void token_vector_free(token_vector_t *self);
// grow size of token vector
void token_vector_grow(token_vector_t *self, size_t count);
// append a token to token vector
size_t token_vector_append(token_vector_t *self, token_t token);

// Tokenizer
//

// tokenize string to tokens
void token_vector_stokenize(token_vector_t *self, const char *string);

// read FILE and tokenize it
void token_vector_ftokenize(token_vector_t *self, FILE* file);
