// Mad Brainfuck Interpreter
// Copyright (C) 2020 By @the_madamin
// dictionary.h: Key-Value dictionary for storing pointers to internal functions

#pragma once

#define DICTIONARY_GROW_SIZE 4

typedef const char * dictionary_key;

typedef struct dictionary {
    dictionary_key *keys;
    void * *values;

    size_t count;
    size_t size;
} dictionary_t;

dictionary_t *dictionary_new(size_t initial_size);
void dictionary_free(dictionary_t *self);

size_t dictionary_append(dictionary_t *self, dictionary_key key, void *value);
void dictionary_grow(dictionary_t *self, size_t count);

void *dictionary_lookup(dictionary_t *self, char *key);
