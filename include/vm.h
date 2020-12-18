// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.h: MadBf Virtual Machine

#pragma once

#include "program.h"

#define MEMORY_SIZE 256

typedef unsigned char cell;

typedef struct {
    cell *memory_pointer;
    size_t program_position;
    function_p program_pointer;
} machine_state;

// Initialize Virtual Machine
void vm_init();
// Free resources used by Virtual Machine
void vm_free();

// Execute a function
void vm_execute(function_p function);

// Run a program
void run(program_t *program);

// Register a function
void register_function(char * function_name, void * function_address);
