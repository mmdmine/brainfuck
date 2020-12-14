// Mad Brainfuck Interpreter
// Copyright (C) 2020 By Mohammad Amin Mollazadeh
// token.c: Token manipulation functions

#include <stdlib.h>

#include "token.h"

token_node_p token_new(token_enum token_type) {
    token_node_p result = malloc(sizeof(struct token_node));
    result->token = token_type;
    result->next = NULL;
    return result;
}

void token_free(token_node_p self) {
    token_node_p current, next;
    current = self;
    next = NULL;

    while (current != NULL) {
        if (current->next != NULL) {
            next = current->next;
        }

        free(current);

        current = next;
        next = NULL;
    }
}

token_node_p token_push(token_node_p self, token_node_p second) {
    if (second == NULL && self == NULL) {
        return NULL;
    }
    if (self == NULL) {
        return second;
    }
    if (second == NULL || second->next != NULL) {
        // TODO: error
        return self;
    }
    second->next = self;
    return second;
}
