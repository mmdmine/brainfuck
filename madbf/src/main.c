// Mad Brainfuck Interpreter
// By @the_madamin

// main.c: Entry point to load MadBf program and execute it

#include "parser.h"
#include "vm.h"
#include "madlib.h"

int main(int argc, char **args) {
    // TODO: check if argument represents a file or a program
    // TODO: if argument represents a file then read the file to string

    char *program_raw = "+[-[<<[+[--->]-[<<<]]]>>>-]>-.---.>..>.<<<<-.<+.>>>>>.>.<<.<-.";

    // compile program
    //
    token_vector_t *tokens = tokenize(program_raw);
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
