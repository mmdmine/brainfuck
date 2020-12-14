#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

struct dictionary {
    dictionary_key *keys;
    void * *values;
    size_t count;
    size_t length;
};

dictionary dictionary_new(int length) {
    dictionary result = malloc(sizeof(struct dictionary));
    result->count = 0;
    result->length = length;
    result->keys = calloc(length, sizeof(dictionary_key));
    result->values = calloc(length, sizeof(void *));
    return result;
}

void dictionary_free(dictionary self) {
    self->length = 0;
    free(self->keys);
    free(self->values);
    free(self);
}

void dictionary_add(dictionary self, dictionary_key key, void *value) {
    if (self->count >= self->length) {
        // TODO: error
        return;
    }
    self->keys[self->count] = key;
    self->values[self->count] = value;
    self->count++;
}

void *dictionary_lookup(dictionary self, char *key) {
    size_t i = 0;
    while (strcmp(self->keys[i], key) != 0) {
        i++;
        if (i >= self->length) {
            // TODO: error
            return NULL;
        }
    }
    return self->values[i];
}
