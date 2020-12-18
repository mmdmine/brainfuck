// Mad Brainfuck Interpreter
// Copyright (C) 2020 Mohammad Amin Mollazadeh
// parser.h: MadBf Parser

#pragma once

#include "token.h"
#include "program.h"

void parse_tokens(token_vector_t *tokens, function_p function);

program_t *parse(char *input);
