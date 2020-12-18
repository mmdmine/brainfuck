// test if tokenizer works correctly

#include <stddef.h>
#include <assert.h>
#include "token.h"

// input value for test
const char *test_program = "++[>+<-],.:Y";

// expected output
const token_t test_program_tokens[] = {
        token_increment,
        token_increment,
        token_open_bracket,
        token_pointer_next,
        token_increment,
        token_pointer_prev,
        token_decrement,
        token_close_bracket,
        token_get_char,
        token_put_char,
        token_call,
        token_fork
};

int main(int argc, char **args) {
    // tokenize program
    token_vector_t *tokens = tokenize(test_program);

    // check if output is correct
    for (size_t i = 0; i < tokens->count; i++) {
        assert(tokens->tokens[i] == test_program_tokens[i]);
    }

    token_vector_free(tokens);

    return 0;
}
