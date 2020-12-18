// Mad Brainfuck Interpreter
// By @the_madamin

// main.c: Entry point to load MadBf program and execute it

#include <stdio.h>

#include "parser.h"
#include "vm.h"
#include "madlib.h"

int main(int argc, char **args) {
    if (argc <= 1) {
        const char *usage_text = "Mad Brainfuck Interpreter\n"
                                 "By @the_madamin\n\n"
                                 "Usage: %s <file name>\n"
                                 "    or %s <program code>\n"
                                 "    or %s -\n";

        char *argv0 = "madbf";

        if (argc > 0) {
            argv0 = args[0];
        }

        printf(usage_text, argv0, argv0, argv0);
    }

    // compile program
    //
    token_vector_t *tokens = token_vector_new(TOKEN_VECTOR_GROW_SIZE);

    // try to open file
    FILE *source_file = fopen(args[1], "r");

    if (source_file == NULL) {
        // try to read argument as program
        token_vector_stokenize(tokens, args[1]);
    }
    else {
        token_vector_ftokenize(tokens, source_file);
    }

    if (tokens->count <= 0) {
        // TODO: error
        fprintf(stderr, "No program in input");
    }

    // function size could be same as tokens count, or even less
    function_t * main_function = function_new(tokens->count);
    parse_tokens(tokens, main_function);

    // free the resources that's used for compiling
    //
    // TODO: free resources used by program_raw
    token_vector_free(tokens);

    // run program on vm
    //
    // initialize virtual machine
    vm_init();
    // load standard library
    madlib_register();
    // TODO: register external libraries, if any
    // execute program on vm
    vm_execute(main_function);

    // free resources that's used by vm
    vm_free();
    function_free(main_function);

    // TODO: return program value

    return 0;
}
