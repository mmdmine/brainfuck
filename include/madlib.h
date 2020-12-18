// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// madlib.h: Standard Library for MadBf

#pragma once

#include "vm.h"

#define MADLIB_FUNCTION_PUT "put"
#define MADLIB_FUNCTION_GET "get"

// Register library functions
void madlib_register();
