// Mad Brainfuck Standard Library
// Copyright (C) 2020 Mohammad Amin Mollazadeh

#pragma once

#include "vm.h"

// Register library functions
void register_library();

// Print cell to standard output
void put(cell input);

// Get one cell from standard input
cell get();
