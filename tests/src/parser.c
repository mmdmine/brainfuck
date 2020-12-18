// Test if parser works correctly

#include <assert.h>
#include <string.h>

#include "parser.h"
#include "madlib.h"

// input for test
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
        token_put_char
};

// expected output
const opcode_type_t test_program_opcodes[] = {
        opcode_type_increment,
        opcode_type_increment,
        opcode_type_move_next,
        opcode_type_increment,
        opcode_type_move_prev,
        opcode_type_decrement,
        opcode_type_ifjump,
        opcode_type_calli,
        opcode_type_calli
};

// expected values for jump_data
const size_t jump_data[] = {
        2
};

// exptected values fro calli_data
const char * calli_data[] = {
        MADLIB_FUNCTION_GET,
        MADLIB_FUNCTION_PUT
};

int main(int argc, char **args) {
    // create token_vector_t
    token_vector_t *tokens = token_vector_new(sizeof(test_program_tokens) / sizeof(token_t));
    for (size_t i = 0; i < tokens->size; i++) {
        token_vector_append(tokens, test_program_tokens[i]);
    }

    // create new function
    function_t *test_function = function_new(sizeof(test_program_opcodes)/sizeof(opcode_type_t));

    parse_tokens(tokens, test_function);

    token_vector_free(tokens);

    // test for function body
    size_t jump_i = 0; // jump_data index
    size_t calli_i = 0; // calli_data index
    for (size_t i = 0; i < test_function->count; i++) {
        // test if opcode type is correct
        assert(test_function->opcodes[i].type == test_program_opcodes[i]);

        // test if jump_data is correct
        if (test_function->opcodes[i].type == opcode_type_ifjump) {
            assert(test_function->opcodes[i].data.jump_data == jump_data[jump_i]);
            jump_i++;
        }
        // test if calli_data is correct
        else if (test_function->opcodes[i].type == opcode_type_calli) {
            assert(strcmp(test_function->opcodes[i].data.calli_data, calli_data[calli_i]) == 0);
            calli_i++;
        }
    }

    function_free(test_function);

    return 0;
}
