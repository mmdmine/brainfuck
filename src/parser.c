// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// parser.h: Parse input string to program

#include <stdlib.h>

#include "parser.h"
#include "token.h"

token_node_p tokenizer(char *input) {
    char *ip = input;
    token_node_p result = NULL;
    token_node_p new_child = NULL;
    while (*ip != 0) {
        switch (*ip) {
            case '>':
                new_child = token_new(token_pointer_next);
                break;
            case '<':
                new_child = token_new(token_pointer_prev);
                break;
            case '+':
                new_child = token_new(token_increment);
                break;
            case '-':
                new_child = token_new(token_decrement);
                break;
            case '[':
                new_child = token_new(token_start_loop);
                break;
            case ']':
                new_child = token_new(token_end_loop);
                break;
            case '.':
                new_child = token_new(token_print);
                break;
            case ',':
                new_child = token_new(token_read);
                break;
            default:
                // ignore character
                ip++;
                continue;
        }
        result = token_push(result, new_child);
        ip++;
    }
    return result;
}

program parse(char *input) {
    token_node_p tokens = tokenizer(input);

    // TODO: Parse tokens

    program result;
    result.raw = input;
    return result;
}
