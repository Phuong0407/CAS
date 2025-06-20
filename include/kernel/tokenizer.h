/******************************************************************************
 * 
 * @file parser.h
 * @date June 14, 2025
 * @author Diep-Thanh-Phuong
 * @copyright
 *  Copyright (c) 2025 Diep-Thanh-Phuong
 *  This file is part of CAS.
 * 
 *  CAS is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  CAS is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 *  License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with CAS. If not, see <https://www.gnu.org/licenses/>.
 * 
 *****************************************************************************/

#ifndef kernel_tokenizer_h
#define kernel_tokenizer_h

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

typedef enum {
    NUM,
    SYM,
    OP,
    END
} TOKENTYPE;

#define TOKEN_STR_SIZE              16
#define MAX_NUM_TOKENS              10000
#define TOKEN_INVALID_CHAR          -1
#define TOKEN_OVERFLOW              -2
#define NUM_REAL                    1
#define NUM_INT                     2
#define NUM_DOT_INVALID             -1
#define NUM_CHAR_INVALID            -2
#define NO_ERR                      0

static const unsigned char op_lookup[256] = {
    ['+'] = 1, ['-'] = 1,
    ['*'] = 1, ['/'] = 1,
    ['^'] = 1,
    ['.'] = 1,

    ['('] = 1, [')'] = 1,
    ['['] = 1, [']'] = 1,
    ['{'] = 1, ['}'] = 1,
    ['='] = 1
};

typedef struct {
    TOKENTYPE type;
    char text[TOKEN_STR_SIZE];
} Token_t;

int tokenize(const char *input, Token_t *tokens, int* num_tokens);

#endif // kernel_tokenizer_h