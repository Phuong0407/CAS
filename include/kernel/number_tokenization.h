/******************************************************************************
 * 
 * @file number_tokenization.h
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

#ifndef include_kernel_number_tokenization_h
#define include_kernel_number_tokenization_h

#include <token.h>

typedef enum {
    N_STT,
    N_ERR,
    N_INT,
    N_DOT, N_DEC,
    N_EXP, N_SGN, N_FLP
} NUMSTATE;

const static NUMSTATE num_fsmtab[8][5] = {
    [N_STT] = {N_INT,   N_DOT,  N_ERR,  N_STT,  N_STT},
    [N_INT] = {N_INT,   N_DEC,  N_EXP,  N_STT,  N_STT},
    [N_DOT] = {N_DEC,   N_ERR,  N_ERR,  N_ERR,  N_ERR},
    [N_DEC] = {N_DEC,   N_ERR,  N_EXP,  N_STT,  N_STT},
    [N_EXP] = {N_FLP,   N_ERR,  N_ERR,  N_SGN,  N_STT},
    [N_SGN] = {N_FLP,   N_ERR,  N_ERR,  N_ERR,  N_ERR},
    [N_FLP] = {N_FLP,   N_ERR,  N_ERR,  N_STT,  N_STT},
};

static const int numtok_term[] = {
    [N_STT] = 1,
    [N_ERR] = 1,
    [N_INT] = 0,
    [N_DOT] = 0,
    [N_DEC] = 0,
    [N_EXP] = 0,
    [N_SGN] = 0,
    [N_FLP] = 0,
};

NUMSTATE tokenize_number(char *tok, const char *s, int i);
const char* state_str(NUMSTATE s);

#endif // include_kernel_number_tokenization_h