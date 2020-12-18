// Mad Brainfuck Interpreter
// By @the_madamin

// parser.h: Parser Header file

#pragma once

#include "token.h"
#include "program.h"

// parse tokens and generate opcodes for vm
void parse_tokens(token_vector_t *tokens, function_t *function);
