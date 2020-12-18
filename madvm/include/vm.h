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
    function_t *program_pointer;
} machine_state;

void vm_init();
void vm_free();
void vm_execute(function_t *function);
void vm_run_native_function(char * function_name);
void vm_register_native_function(char * function_name, void * function_address);
