// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// main.c: Interpreter's entry point

#include "parser.h"
#include "vm.h"
#include "madlib.h"

int main(int argc, char **args) {
    // TODO: check if argument represents a file or a program
    // TODO: if argument represents a file then read the file to string

    char *program_raw = "+[-[<<[+[--->]-[<<<]]]>>>-]>-.---.>..>.<<<<-.<+.>>>>>.>.<<.<-.";

    program program_parsed = parse(program_raw);

    // TODO: free resources used by program_raw

    // Initialize virtual machine
    vm_init();
    madlib_register();
    // TODO: register external libraries, if any

    run(program_parsed);

    vm_free();

    // TODO: return program value

    return 0;
}
