// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.h: Virtual Machine Functions and Types

#pragma once

typedef unsigned char cell;

typedef struct {
    char *raw;
} program;

typedef struct {
    cell *memory_pointer;
} machine_state;

// Run a program
void run(program program);

// Register a function
void register_function(const char *function_name, void *function_address);
