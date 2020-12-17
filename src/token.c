// Mad Brainfuck Interpreter
// Copyright (C) 2020 By Mohammad Amin Mollazadeh
// token.c: Token manipulation functions

#include <stdlib.h>

#include "token.h"

token_vector_t *token_vector_new(size_t initial_size) {
    token_vector_t *result = malloc(sizeof(token_vector_t));
    result->tokens = calloc(initial_size, sizeof(token_t));
    result->size = initial_size;
    result->count = 0;
    return result;
}

void token_vector_free(token_vector_t *self) {
    free(self->tokens);
    free(self);
}

void token_vector_grow(token_vector_t *self, size_t count) {
    size_t new_size = self->size + count;
    size_t total_bytes = new_size * sizeof(token_t);
    self->tokens = realloc(self->tokens, total_bytes);
    self->size = new_size;
}

size_t token_vector_append(token_vector_t *self, token_t token) {
    if (self->count >= self->size) {
        token_vector_grow(self, TOKEN_VECTOR_GROW_SIZE);
    }
    self->tokens[self->count] = token;
    return self->count++;
}

token_vector_t *tokenize(const char *input) {
    const char *ip = input;
    token_vector_t *result = token_vector_new(TOKEN_VECTOR_GROW_SIZE);
    while (*ip != 0) {
        switch (*ip) {
            case '>':
                token_vector_append(result, token_pointer_next);
                break;
            case '<':
                token_vector_append(result, token_pointer_prev);
                break;
            case '+':
                token_vector_append(result, token_increment);
                break;
            case '-':
                token_vector_append(result, token_decrement);
                break;
            case '[':
                token_vector_append(result, token_start_loop);
                break;
            case ']':
                token_vector_append(result, token_end_loop);
                break;
            case '.':
                token_vector_append(result, token_print);
                break;
            case ',':
                token_vector_append(result, token_read);
                break;
            default:
                // ignore character
                ip++;
                continue;
        }
        ip++;
    }
    return result;
}
