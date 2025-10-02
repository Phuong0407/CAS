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

#endif // include_kernel_symbol_tokenization_h