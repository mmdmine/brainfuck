// test for "madvm/src/program.c"

#include <stddef.h>
#include <assert.h>

#include "program.h"

int main(int argc, char **argv) {
    // test program_new
    program_t *test_program = program_new();
    assert(test_program != NULL);
    
    program_free(test_program);
}
