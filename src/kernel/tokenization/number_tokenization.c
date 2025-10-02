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

#include <kernel/tokenization/number_tokenization.h>

NUMSTATE tokenize_number(Token_t *tok, const char *s, int *i) {
    int j = 0;
    NUMSTATE state = N_STT;

    while(s[*i] != '\0' && j < MAXTOKLEN - 1) {
        char c = s[*i];
        uint8_t cls = num_tab[(unsigned char)c];
        NUMSTATE nextstate = num_fsmtab[state][cls];
        if (numtok_term[nextstate]) break;
        tok->tokn[tok->ntok][j++] = s[(*i)++];
        state = nextstate;
    }
    tok->tokn[tok->ntok][j] = '\0';
    switch (state) {
        case N_INT: return N_INT;
        case N_DEC: return N_DEC;
        case N_FLP: return N_FLP;
        case N_STT: return N_STT;
        default:    return N_ERR;
    }
    return N_ERR;
}

const char* state_str(NUMSTATE s) {
    switch (s) {
        case N_INT: return "INT";
        case N_DEC: return "DEC";
        case N_FLP: return "FLP";
        case N_STT: return "STT";
        case N_ERR: return "ERR";
        default:    return "???";
    }
}