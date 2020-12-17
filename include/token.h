// Mad Brainfuck Interpreter
// Copyright (C) 2020 By Mohammad Amin Mollazadeh
// token.h: MadBf Tokenizer

#pragma once

#include <stddef.h>

#define TOKEN_VECTOR_GROW_SIZE 4

enum token_types {
    token_pointer_next,
    token_pointer_prev,
    token_increment,
    token_decrement,
    token_start_loop,
    token_end_loop,
    token_print,
    token_read
};

typedef enum token_types token_t;

struct token_vector {
    token_t *tokens;
    size_t count;
    size_t size;
};

typedef struct token_vector token_vector_t;

token_vector_t *token_vector_new(size_t initial_size);
void token_vector_free(token_vector_t *self);
void token_vector_grow(token_vector_t *self, size_t count);
size_t token_vector_append(token_vector_t *self, token_t token);

token_vector_t *tokenize(const char *input);
