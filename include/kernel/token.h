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

#define MAXNTOK             512
#define MAXTOKLEN           64

#define MAXNTOK_OVERFLOW    -1
#define MAXTOKLEOVERFLOW    -2


typedef enum { NUM, PRT, OPR, SYM, STT, ERR } TOKEN;

static const uint8_t tok_tab[256] = {
    [0 ... 255]     = ERR,
    [' ']           = STT,
    ['_']           = SYM,
    ['a' ... 'z']   = SYM,
    ['A' ... 'Z']   = SYM,

    ['.']           = NUM,
    ['0' ... '9']   = NUM,

    ['+']           = OPR, 
    ['-']           = OPR,
    ['*']           = OPR, 
    ['/']           = OPR,
    ['^']           = OPR, 
    ['!']           = OPR,

    ['(']           = PRT, 
    [')']           = PRT,
    ['<']           = PRT, 
    ['>']           = PRT,
};


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
    [T_OPR] = {T_STT,   T_STT,  T_ERR,  T_STT,  T_STT,  T_ERR},
    [T_SYM] = {T_ERR,   T_STT,  T_STT,  T_ERR,  T_STT,  T_ERR},
};

static const int token_term[] = {
    [T_ERR] = 1,
    [T_STT] = 2,
    [T_NUM] = 0,
    [T_PRT] = 0,
    [T_OPR] = 0,
    [T_SYM] = 0,
};



/**
 *   if type == NUM
 *  sbtype = 0 INT 
 *   sbtype = 1 DEC
 *   sbtype = 2 FLP

    if type == OPR
    sbtype = 0 UNITY_POSSIBLE    (+-)
    sbtype = 1 UNITY_IMPOSSIBLE  (rest, * / ^ ! )

 *  if type == PRT
 *  sbtype = 0 LEFT_PRT ( <
 *  sbtype = 1 RIGHT_PRT ) >

 *  if type == SYM
 *  sbtype = 0 DEFAULT
 */
typedef struct {
    char tokn[MAXNTOK][MAXTOKLEN];
    TOKEN type[MAXNTOK];
    int sbtype[MAXNTOK];
    int ntok;
} Token_t;

static const uint8_t opr_oprsbtype[] = {
    ['+'] = 0, 
    ['-'] = 0,
    ['*'] = 1, 
    ['/'] = 1,
    ['^'] = 1, 
    ['!'] = 1,
};

static const uint8_t prt_prtsbtype[] = {
    ['('] = 0, 
    ['<'] = 0,
    [')'] = 1, 
    ['>'] = 1,
};

extern Token_t  *create_tokens();
extern void     free_tokens(Token_t *tokens);

#endif // include_kernel_token_h