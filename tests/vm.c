#include <assert.h>
#include "program.h"
#include "vm.h"

machine_state *vm_state = NULL;

void test_calli(machine_state *state) {
    *(state->memory_pointer) = 'A';
}

void save_state(machine_state *state) {
    vm_state = state;
}

int main(int argc, char **args) {
    vm_init();

    register_function("test", test_calli);
    register_function("save_state", save_state);

    // test_function: + > : > ++ [ > + < - ] < < :
    function_p test_function = function_new(14);
    function_omit_increment(test_function);
    function_omit_move_next(test_function);
    function_omit_calli(test_function, "test");
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
    function_omit_calli(test_function, "save_state");

    vm_execute(test_function);

    assert(vm_state != NULL);
    // expected state:
    //  [0]: 1
    //  [1]: 'A'
    //  [2]: 0
    //  [3]: 2
    assert(vm_state->memory_pointer[0] == 1);
    assert(vm_state->memory_pointer[1] == 'A');
    assert(vm_state->memory_pointer[2] == 0);
    assert(vm_state->memory_pointer[3] == 2);

    function_free(test_function);
    vm_free();

    return 0;
}
