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

void handle_stt(Token_t *toks, const char *s, int *i) {
    while (s[*i] != '\0' && isspace((unsigned char)s[*i])) {
        (*i)++;
    }
}

void handle_num(Token_t* toks, const char* s, int *i) {
    NUMSTATE numtype        = tokenize_number(toks, s, i);
    toks->type[toks->ntok] = NUM;
    toks->sbtype[toks->ntok]  = numtoken_numsbtype[numtype];
    (toks->ntok)++;
}

void handle_opr(Token_t* toks, const char* s, int *i) {
    (*toks).tokn[toks->ntok][0] = s[*i];
    (*toks).tokn[toks->ntok][1] = '\0';
    toks->type[toks->ntok]    = OPR;
    toks->sbtype[toks->ntok]  = opr_oprsbtype[(unsigned int)s[*i]];
    (toks->ntok)++;
    (*i)++;
}

void handle_prt(Token_t* toks, const char* s, int *i) {
    // printf("%d\t%d\n", toks->ntok, *i);
    // printf("%d\n", s[*i]);
    (*toks).tokn[toks->ntok][0] = s[*i];
    (*toks).tokn[toks->ntok][1] = '\0';
    toks->type[toks->ntok]    = PRT;
    toks->sbtype[toks->ntok]  = prt_prtsbtype[(unsigned int)s[*i]];
    (toks->ntok)++;
    (*i)++;
}

void handle_sym(Token_t* toks, const char* s, int *i) {
    tokenize_symbol(toks, s, i);
    toks->type[toks->ntok]    = SYM;
    toks->sbtype[toks->ntok]  = 0;
    (toks->ntok)++;
}

TOKENSTATE tokenize(Token_t *toks, const char *s) {
    int i = 0;
    TOKENSTATE state = T_STT;

    while (s[i] != '\0' && toks->ntok < MAXNTOK - 1) {
        uint8_t cls = tok_tab[(unsigned char)s[i]];
        TOKENSTATE nextstate = tok_fsmtab[state][cls];
        if (token_term[nextstate] == 1) break;
        handler_tab[nextstate](toks, s, &i);
        state = nextstate;
    }
    return state;
}
