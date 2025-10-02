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

#ifndef include_kernel_symbol_tokenization_h
#define include_kernel_symbol_tokenization_h

#include <kernel/token.h>

typedef enum { SDIG, SUDC, SCHR, SSTT, SOTHER } SYMTOKEN;

const static uint8_t sym_tab[256] = {
    [0 ... 255]     = SOTHER,
    ['0' ... '9']   = SDIG,
    ['a' ... 'z']   = SCHR,
    ['A' ... 'Z']   = SCHR,
    ['_']           = SUDC,
};

typedef enum {
    S_STT,
    S_SYM,
} SYMSTATE;

static const SYMSTATE sym_fsmtab[6][6] = {
    [S_STT] = {S_STT,   S_SYM,  S_SYM,  S_STT,  S_STT},
    [S_SYM] = {S_SYM,   S_SYM,  S_SYM,  S_STT,  S_STT},
};

void tokenize_symbol(Token_t *toks, const char *s, int *i);

#endif /* include_kernel_symbol_tokenization_h */