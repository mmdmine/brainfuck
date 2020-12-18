// test for madvm/src/dictionary.c

#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "dictionary.h"

#define DICTIONARY_INITIAL_SIZE 4

#define APPEND_TEST(I, KEY, VALUE) dictionary_append(dic, (KEY), (VALUE)); \
assert(dic->count == I+1);                                                 \
assert(strcmp(dic->keys[I], (KEY)) == 0);                                  \
assert(dic->values[I] == (VALUE));

#define LOOKUP_TEST(I, KEY, VALUE) {                 \
void *lookup_result = dictionary_lookup(dic, (KEY)); \
assert(lookup_result == dic->values[I]);             \
assert(lookup_result == (VALUE));                    \
}

int test_function(int x) { return x; }

int main(int argc, char **argv) {
    // test dictionary_new
    dictionary_t *dic = dictionary_new(DICTIONARY_INITIAL_SIZE);
    assert(dic != NULL);
    assert(dic->keys != NULL);
    assert(dic->values != NULL);
    assert(dic->size == DICTIONARY_INITIAL_SIZE);
    assert(dic->count == 0);

    // test dictionary_append and dictionary_grow
    APPEND_TEST(0, "test1", NULL)
    APPEND_TEST(1, "test2", NULL)
    APPEND_TEST(2, "test3", NULL)
    APPEND_TEST(3, "test_function", test_function)

    assert(dic->size == DICTIONARY_INITIAL_SIZE);

    APPEND_TEST(4, "test5", NULL)

    assert(dic->size == DICTIONARY_INITIAL_SIZE + DICTIONARY_GROW_SIZE);

    dictionary_grow(dic, 1);
    assert(dic->size == DICTIONARY_INITIAL_SIZE + DICTIONARY_GROW_SIZE + 1);

    // test dictionary_lookup
    LOOKUP_TEST(0, "test1", NULL)
    LOOKUP_TEST(1, "test2", NULL)
    LOOKUP_TEST(2, "test3", NULL)
    LOOKUP_TEST(3, "test_function", test_function)
    LOOKUP_TEST(4, "test5", NULL)

    dictionary_free(dic);
}
