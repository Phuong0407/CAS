/******************************************************************************
 * 
 * @file tokenization.c
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



#include <kernel/tokenization.h>
#include <kernel/number_tokenization.h>
#include <kernel/symbol_tokenization.h>


TokenHandler handler_tab[] = {
    [T_NUM] = handle_num,
    [T_OPR] = handle_opr,
    [T_PRT] = handle_prt,
    [T_SYM] = handle_sym,
    [T_STT] = handle_stt,
};

void handle_stt(Token_t *tok, const char *s, int *i, int *ntok) {
    while (s[*i] != '\0' && isspace((unsigned char)s[*i])) {
        (*i)++;
    }
}

void handle_num(Token_t* toks, const char* s, int *i, int *ntok) {
    NUMSTATE numtype    = tokenize_number(&toks[*ntok], s, i);
    toks[*ntok].type    = NUM;
    toks[*ntok].sbtype  = numtoken_numsbtype[numtype];
    (*ntok)++;
}

void handle_opr(Token_t* toks, const char* s, int *i, int *ntok) {
    toks[*ntok].tokn[0] = s[*i];
    toks[*ntok].tokn[1] = '\0';
    toks[*ntok].type    = OPR;
    toks[*ntok].sbtype  = opr_oprsbtype[(unsigned int)s[*i]];
    (*ntok)++;
    (*i)++;
}

void handle_prt(Token_t* toks, const char* s, int *i, int *ntok) {
    toks[*ntok].tokn[0] = s[*i];
    toks[*ntok].tokn[1] = '\0';
    toks[*ntok].type    = PRT;
    toks[*ntok].sbtype  = prt_prtsbtype[(unsigned int)s[*i]];
    (*ntok)++;
    (*i)++;
}

void handle_sym(Token_t* toks, const char* s, int *i, int *ntok) {
    tokenize_symbol(&toks[(*ntok)], s, i);
    toks[*ntok].type    = SYM;
    toks[*ntok].sbtype  = 0;
    (*ntok)++;
}

TOKENSTATE tokenize(Token_t *toks, const char *s, int *ntok) {
    int i = 0;
    TOKENSTATE state = T_STT;

    while (s[i] != '\0' && *ntok < MAXNTOK - 1) {
        uint8_t cls = tok_tab[(unsigned char)s[i]];
        TOKENSTATE nextstate = tok_fsmtab[state][cls];
        if (token_term[state] == 1) break;
        handler_tab[state](toks, s, &i, ntok);
        state = nextstate;
    }
    return state;
}