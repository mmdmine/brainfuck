// Mad Brainfuck Interpreter
// By @the_madamin

// function.h: Virtual Machine Operation Codes Definition

#pragma once

#include <stddef.h>

// Defining opcode type
//

typedef struct opcode opcode_t;

// type of opcodes
typedef enum {
    // increment cell by one
    opcode_type_increment,
    // decrement cell by one
    opcode_type_decrement,
    // move pointer to next cell
    opcode_type_move_next,
    // move pointer to previous cell
    opcode_type_move_prev,
    // jump to target if cell is not zero
    opcode_type_ifjump,
    // call native function
    opcode_type_calli,
    // TODO: opcode for calling madbf functions
} opcode_type_t;

// arguments of calli and jump opcodes
typedef union {
    // name of the function to be executed as string
    char * calli_data;
    // position to jump
    size_t jump_data;
} opcode_data_t;

struct opcode {
    opcode_type_t type;
    opcode_data_t data;
};
