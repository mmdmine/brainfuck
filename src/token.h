// Mad Brainfuck Interpreter
// Copyright (C) 2020 By Mohammad Amin Mollazadeh
// token.h: Tokenizer types and functions

#pragma once

typedef enum token_types {
    token_pointer_next,
    token_pointer_prev,
    token_increment,
    token_decrement,
    token_start_loop,
    token_end_loop,
    token_print,
    token_read
} token_enum;

typedef struct token_node * token_node_p;

struct token_node {
    token_enum token;
    token_node_p next;
};

token_node_p token_new();
void token_free(token_node_p self);
token_node_p token_push(token_node_p self, token_node_p second);
