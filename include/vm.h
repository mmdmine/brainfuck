// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.h: MadBf Virtual Machine

#pragma once

typedef unsigned char cell;

typedef struct {
    char *raw;
} program;

typedef struct {
    cell *memory_pointer;
} machine_state;

// Initialize Virtual Machine
void vm_init();
// Free resources used by Virtual Machine
void vm_free();

// Run a program
void run(program program);

// Register a function
void register_function(const char *function_name, void *function_address);
