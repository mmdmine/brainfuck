// Mad Brainfuck Interpreter
// By @the_madamin

// vm.h: Virtual Machine definition

#pragma once

#include <stddef.h>
#include <limits.h>

#include "program.h"

// Total memory cells
#define MEMORY_SIZE 256

// Each memory cell is an unsigned char
typedef unsigned char cell;

// Minimum and Maximum of cell
#define CELL_MIN 0
#define CELL_MAX UCHAR_MAX

// Struct which stores virtual machine's state
typedef struct {
    cell memory[MEMORY_SIZE];
    function_t *function;

    size_t memory_position;
    size_t function_position;
} machine_state;

// Virtual Machine Manipulation functions
//

// Initialize virtual machine and allocate needed spaces
void vm_init();
// Free resources that's used by vm
void vm_free();

void vm_execute(function_t *function);

void vm_register_native_function(char * function_name, void * function_address);
void vm_execute_native_function(char * function_name);
