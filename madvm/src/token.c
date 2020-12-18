// Mad Brainfuck Interpreter
// By @the_madamin

// token.c: Token Vector manipulation functions

#include <stdlib.h>
#include <assert.h>

#include "token.h"

token_vector_t *token_vector_new(size_t initial_size) {
    assert(initial_size != 0);

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
    // grow vector if it reached bound
    if (self->count >= self->size) {
        token_vector_grow(self, TOKEN_VECTOR_GROW_SIZE);
    }

    self->tokens[self->count] = token;

    return self->count++;
}

void token_vector_append_char(token_vector_t *self, char c) {
    switch (c) {
        case '>':
            token_vector_append(self, token_pointer_next);
            break;
        case '<':
            token_vector_append(self, token_pointer_prev);
            break;
        case '+':
            token_vector_append(self, token_increment);
            break;
        case '-':
            token_vector_append(self, token_decrement);
            break;
        case '[':
            token_vector_append(self, token_open_bracket);
            break;
        case ']':
            token_vector_append(self, token_close_bracket);
            break;
        case '.':
            token_vector_append(self, token_put_char);
            break;
        case ',':
            token_vector_append(self, token_get_char);
            break;
        case ':':
            token_vector_append(self, token_call);
            break;
        case 'Y':
            token_vector_append(self, token_fork);
            break;
        default:
            // ignore character
            break;
    }
}

token_vector_t *tokenize(const char *input) {
    token_vector_t *result = token_vector_new(TOKEN_VECTOR_GROW_SIZE);
    token_vector_stokenize(result, input);
    return result;
}

void token_vector_stokenize(token_vector_t *self, const char *string) {
    const char *ip = string;

    // iterate over string and get token for each char
    while (*ip != 0) {
        token_vector_append_char(self, *ip);
        ip++;
    }
}

void token_vector_ftokenize(token_vector_t *self, FILE* file) {
    int c;

    while ((c = fgetc(file)) != EOF) {
        token_vector_append_char(self, (char)c);
    }
}
