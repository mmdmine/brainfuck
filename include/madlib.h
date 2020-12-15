// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// madlib.h: Standard Library for MadBf

#pragma once

#include "vm.h"

// Register library functions
void madlib_register();

// Print cell to standard output
void put(machine_state *state);

// Get one cell from standard input
void get(machine_state *state);
