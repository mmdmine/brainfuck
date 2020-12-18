// test madvm/src/token.c

#include <stddef.h>
#include <assert.h>

#include "token.h"

#define VECTOR_INITIAL_SIZE 4

#define APPEND_TEST(I, TOKEN) token_vector_append(tokens, (TOKEN)); \
assert(tokens->count == I+1);                                       \
assert(tokens->tokens[I] == (TOKEN));

int main(int argc, char **argv) {
    // test token_vector_new
    token_vector_t *tokens = token_vector_new(VECTOR_INITIAL_SIZE);
    assert(tokens != NULL);
    assert(tokens->tokens != NULL);
    assert(tokens->count == 0);
    assert(tokens->size == VECTOR_INITIAL_SIZE);

    // test token_vector_append and test_vector_grow
    APPEND_TEST(0, token_increment)
    APPEND_TEST(1, token_decrement)
    APPEND_TEST(2, token_pointer_next)
    APPEND_TEST(3, token_pointer_prev)

    assert(tokens->size == VECTOR_INITIAL_SIZE);

    APPEND_TEST(4, token_open_bracket)

    assert(tokens->size == VECTOR_INITIAL_SIZE + TOKEN_VECTOR_GROW_SIZE);

    token_vector_grow(tokens, 1);

    assert(tokens->size == VECTOR_INITIAL_SIZE + TOKEN_VECTOR_GROW_SIZE + 1);

    token_vector_free(tokens);

    tokens = token_vector_new(8);
    token_vector_stokenize(tokens, "+-<>[]:Y");
    assert(tokens->count == 8);

    token_t expected[] = {
            token_increment,
            token_decrement,
            token_pointer_prev,
            token_pointer_next,
            token_open_bracket,
            token_close_bracket,
            token_call,
            token_fork
    };

    for (size_t i = 0; i < tokens->count; i++) {
        assert(tokens->tokens[i] == expected[i]);
    }

    token_vector_free(tokens);

#if _POSIX_C_SOURCE >= 200809L
    tokens = token_vector_new(8);

    char *source_string = "+-<>[]:Y";
    FILE * source_file = fmemopen(source_string, 9, "r");

    assert(source_file != NULL);

    token_vector_ftokenize(tokens, source_file);

    fclose(source_file);

    assert(tokens->count == 8);

    for (size_t i = 0; i < tokens->count; i++) {
        assert(tokens->tokens[i] == expected[i]);
    }

    token_vector_free(tokens);
#endif
}