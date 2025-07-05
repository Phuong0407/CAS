#include <kernel/token.h>
#include <assert.h>

Token_t *create_tokens() {
    Token_t *tokens = calloc(1, sizeof(Token_t));
    assert(tokens != NULL);
    return tokens;
}

void free_tokens(Token_t *tokens) {
    if (tokens) {
        free(tokens);
    }
}