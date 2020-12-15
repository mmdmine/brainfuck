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

token_node_p tokenize(char *input) {
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
