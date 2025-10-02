/******************************************************************************
 * 
 * @file number_tokenization.c
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

#include <kernel/tokenization/symbol_tokenization.h>

void tokenize_symbol(Token_t *tok, const char *s, int *i) {
    int j = 0;

    SYMSTATE state = S_STT;
    while(s[*i] != '\0' && j < MAXTOKLEN - 1) {
        char c = s[*i];
        uint8_t cls = sym_tab[(unsigned char)c];
        SYMSTATE nextstate = sym_fsmtab[state][cls];
        if (nextstate == S_STT) break;
        tok->tokn[tok->ntok][j++] = s[(*i)++];
        state = nextstate;
    }
    tok->tokn[tok->ntok][j] = '\0';
}