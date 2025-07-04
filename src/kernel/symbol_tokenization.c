#include <kernel/symbol_tokenization.h>

void tokenize_symbol(Token_t *tok, const char *s, int *i) {
    int j = 0;

    SYMSTATE state = S_STT;
    while(s[*i] != '\0' && j < MAXTOKLEN - 1) {
        char c = s[*i];
        uint8_t cls = sym_tab[(unsigned char)c];
        SYMSTATE nextstate = sym_fsmtab[state][cls];
        if (nextstate == S_STT) break;
        tok->tokn[j++] = s[(*i)++];
        state = nextstate;
    }
    tok->tokn[j] = '\0';
}