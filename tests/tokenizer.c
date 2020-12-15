#include <assert.h>
#include "token.h"

const char *test_program = "++[>+<-],.";

const token_enum test_program_tokens[] = {
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
    token_node_p tokens = tokenize(test_program);

    // iterate over tokens and compare them with expected value
    int i = (sizeof(test_program_tokens) / sizeof(token_enum));
    token_node_p current = tokens;
    while (current != NULL) {
        token_enum expected = test_program_tokens[--i];
        assert(current->token == expected);
        current = current->next;
    }

    token_free(tokens);

    return 0;
}
