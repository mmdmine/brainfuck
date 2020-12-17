// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// parser.h: Parse input string to program

#include "parser.h"
#include "token.h"

program parse(char *input) {
    token_vector_t *tokens = tokenize(input);

    // TODO: Parse tokens

    program result;
    result.raw = input;
    return result;
}
