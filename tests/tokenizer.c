#include <stddef.h>
#include <assert.h>
#include "token.h"

const char *test_program = "++[>+<-],.";

const token_t test_program_tokens[] = {
        token_increment,
        token_increment,
        token_start_loop,
        token_pointer_next,
        token_increment,
        token_pointer_prev,
        token_decrement,
        token_end_loop,
        token_read,
        token_print
};

int main(int argc, char **args) {
    token_vector_t *tokens = tokenize(test_program);

    for (int i = 0; i < tokens->count; i++) {
        assert(tokens->tokens[i] == test_program_tokens[i]);
    }

    token_vector_free(tokens);

    return 0;
}
