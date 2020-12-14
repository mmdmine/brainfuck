#pragma once

typedef struct dictionary * dictionary;

typedef const char * dictionary_key;

// allocate new space for dictionary
dictionary dictionary_new(int length);
// deallocate space used by dictionary
void dictionary_free(dictionary self);
// add new entry to dictionary
void dictionary_add(dictionary self, dictionary_key key, void *value);
// lookup for a key in dictionary then return its value
void *dictionary_lookup(dictionary self, char *key);
