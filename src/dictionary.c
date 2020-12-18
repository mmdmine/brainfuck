#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

dictionary_t *dictionary_new(size_t initial_size) {
    dictionary_t *result = malloc(sizeof(dictionary_t));
    result->keys = calloc(initial_size, sizeof(dictionary_key));
    result->values = calloc(initial_size, sizeof(void *));
    result->count = 0;
    result->size = initial_size;
    return result;
}

void dictionary_free(dictionary_t *self) {
    free(self->keys);
    free(self->values);
    free(self);
}

size_t dictionary_append(dictionary_t *self, dictionary_key key, void *value) {
    if (self->count >= self->size) {
        dictionary_grow(self, DICTIONARY_GROW_SIZE);
    }
    self->keys[self->count] = key;
    self->values[self->count] = value;
    return self->count++;
}

void dictionary_grow(dictionary_t *self, size_t count) {
    size_t new_size = self->size + count;
    size_t total_key_bytes = new_size * sizeof(dictionary_key);
    size_t total_value_bytes = new_size * sizeof(void *);
    self->keys = realloc(self->keys, total_key_bytes);
    self->values = realloc(self->values, total_value_bytes);
    self->size = new_size;
}

void *dictionary_lookup(dictionary_t *self, char *key) {
    for (size_t i = 0; i < self->count; i++) {
        if (strcmp(self->keys[i], key) == 0) {
            return self->values[i];
        }
    }
    // TODO: Error
    return NULL;
}
