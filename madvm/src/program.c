// Mad Brainfuck Interpreter
// By @the_madamin

// program.c: Program manipulation functions implementation

#include <stdlib.h>

#include "program.h"

program_t *program_new() {
    program_t *result = malloc(sizeof(program_t));
    result->main = NULL;
    return result;
}

void program_free(program_t *self) {
    if (self->main != NULL) {
        free(self->main);
    }
    free(self);
}
