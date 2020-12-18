// Mad Brainfuck Interpreter
// By @the_madamin

// madlib.h: Standard Library Header file

#pragma once

// Load library to virtual machine
void madlib_register();

// Standard Library Functions
//

// Put a character from current cell to stdout
#define MADLIB_FUNCTION_PUT "put"
// Read a character from stdin to current cell
#define MADLIB_FUNCTION_GET "get"
