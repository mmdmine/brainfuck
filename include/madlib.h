// Mad Brainfuck Standard Library
// Copyright (C) 2020 Mohammad Amin Mollazadeh

#pragma once

#include "vm.h"

// Register library functions
void register_library();

// Print cell to standard output
void put(machine_state *state);

// Get one cell from standard input
void get(machine_state *state);
