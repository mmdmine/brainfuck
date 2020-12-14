cmake_minimum_required (VERSION 3.8)

project ("Brainfuck")

add_executable (madbf
        "src/Brainfuck.c"
        "src/Brainfuck.h"
        "src/vm.c"
        "src/vm.h"
        "src/parser.c"
        "src/parser.h")
