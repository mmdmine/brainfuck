// test if virtual machine works correctly

#include <assert.h>

#include "program.h"
#include "vm.h"

// machine state at the end of program
machine_state *vm_state = NULL;

// native function test
#define TEST_FUNCTION_TEST_CALLI "test"
void test_calli(machine_state *state) {
    state->memory[state->memory_position] = 'A';
}

// save machine state
#define TEST_FUNCTION_SAVE_STATE "save"
void save_state(machine_state *state) {
    vm_state = state;
}

int main(int argc, char **args) {
    vm_init();

    // register native functions used by test
    vm_register_native_function(TEST_FUNCTION_TEST_CALLI, test_calli);
    vm_register_native_function(TEST_FUNCTION_SAVE_STATE, save_state);

    // test_function: + > : > ++ [ > + < - ] < < :

    function_t *test_function = function_new(14);

    function_omit_increment(test_function);
    function_omit_move_next(test_function);
    function_omit_calli(test_function, TEST_FUNCTION_TEST_CALLI);
    function_omit_move_next(test_function);
    function_omit_increment(test_function);
    function_omit_increment(test_function);
    size_t loop_start = function_omit_move_next(test_function);
    function_omit_increment(test_function);
    function_omit_move_prev(test_function);
    function_omit_decrement(test_function);
    function_omit_jump(test_function, loop_start);
    function_omit_move_prev(test_function);
    function_omit_move_prev(test_function);
    function_omit_calli(test_function, TEST_FUNCTION_SAVE_STATE);

    vm_execute(test_function);

    // test if vm state is saved
    assert(vm_state != NULL);
    // test if program executed until the end
    assert(vm_state->function_position == test_function->count);
    // test if memory pointer is pointing first cell
    assert(vm_state->memory_position == 0);
    // expected state:
    //  [0]: 1
    //  [1]: 'A'
    //  [2]: 0
    //  [3]: 2
    assert(vm_state->memory[0] == 1);
    assert(vm_state->memory[1] == 'A');
    assert(vm_state->memory[2] == 0);
    assert(vm_state->memory[3] == 2);

    function_free(test_function);
    vm_free();

    return 0;
}
