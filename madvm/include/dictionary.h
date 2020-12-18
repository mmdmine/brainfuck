// Mad Brainfuck Interpreter
// By @the_madamin

// dictionary.h: name/pointer pair dictionary for native functions

#pragma once

#include <stddef.h>

// Count of new entries to be allocated when vector needs to grow
#define DICTIONARY_GROW_SIZE 4

typedef struct dictionary {
    const char * *keys;
    void * *values;

    // count of entries used in vector
    size_t count;
    // size of allocated space for vector
    size_t size;
} dictionary_t;

// allocate space for a new dictionary
// initial_size: initial size of vector, should be larger than 0
dictionary_t *dictionary_new(size_t initial_size);
// free the resources that's used by dictionary
void dictionary_free(dictionary_t *self);
// grow the space allocated for dictionary by count
void dictionary_grow(dictionary_t *self, size_t count);

// append new entry to dictionary, grow dictionary by DICTIONARY_GROW_SIZE if reached the bounds
size_t dictionary_append(dictionary_t *self, const char * key, void * value);
// look up dictionary for an entry
void *dictionary_lookup(dictionary_t *self, char *key);
