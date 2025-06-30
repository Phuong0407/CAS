/******************************************************************************
 * 
 * @file token.h
 * @date June 29, 2025
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

#ifndef include_kernel_token_h
#define include_kernel_token_h

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define MAXNTOK                     512
#define MAXTOKLEN                   64

#define MAXNTOK_OVERFLOW            -1
#define MAXTOKLEOVERFLOW          -2



typedef uint8_t TokenTable_t;

static const TokenTable_t oprt_tab[256] = {
    [0 ... 255] = 0,
    ['+'] = 1, ['-'] = 1,
    ['*'] = 1, ['/'] = 1,
    ['^'] = 1, ['!'] = 1,
};

static const TokenTable_t prth_tab[256] = {
    [0 ... 255] = 0,
    ['('] = 1, [')'] = 1,
    ['<'] = 1, ['>'] = 1,
};

const static uint8_t num_tab[256] = {
    [0 ... 255] = OTHER,
    ['0' ... '9'] = DIGIT,
    ['e'] = EXP, ['E'] = EXP,
    ['+'] = SIGN, ['-'] = SIGN,
    ['.'] = DOT,
};

typedef enum { NUM, PRT, OPR, SYM, STT, ERR } TOKEN;
typedef enum { DIGIT, DOT, EXP, SIGN, OTHER } NUMTOKEN;

typedef enum {
    T_STT,
    T_ERR,
    T_NUM,
    T_PRT,
    T_OPR,
    T_SYM,
} TOKENSTATE;

const static TOKENSTATE tok_fsmtab[6][6] = {
    [T_STT] = {T_NUM,   T_PRT,  T_OPR,  T_SYM,  T_STT,  T_ERR},
    [T_NUM] = {T_ERR,   T_STT,  T_STT,  T_STT,  T_STT,  T_ERR},
    [T_PRT] = {T_STT,   T_STT,  T_STT,  T_STT,  T_STT,  T_ERR},
    [T_OPR] = {T_STT,   T_ERR,  T_ERR,  T_STT,  T_STT,  T_ERR},
    [T_SYM] = {T_ERR,   T_STT,  T_STT,  T_ERR,  T_STT,  T_ERR},
};

static const int token_term[] = {
    [T_STT] = 1,
    [T_ERR] = 1,
    [T_NUM] = 0,
    [T_PRT] = 0,
    [T_OPR] = 0,
    [T_SYM] = 0,
};



typedef struct {
    char tokn[MAXTOKLEN];
    TOKEN type;
    int stype;
} Token_t;

#endif // include_kernel_token_h