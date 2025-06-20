/******************************************************************************
 * 
 * Copyright (c) 
 * 
 * 
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