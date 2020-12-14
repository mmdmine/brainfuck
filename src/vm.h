// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// vm.h: Virtual Machine Functions and Types

#pragma once

typedef struct {
    char *raw;
} program;

void run(program program);
