#include <tokenizer.h>

static int scan_and_emit(Token_t *tokens, int *num_tokens, const char *input, int i,
                         int (*accept)(int), TOKENTYPE type, int max_len) {
    int len = 0;
    while (accept(input[i + len]) && len < max_len && len < TOKEN_STR_SIZE - 1) {
        len++;
    }

    if (len == 0) return -1;

    strncpy(tokens[*num_tokens].text, &input[i], len);
    tokens[*num_tokens].text[len] = '\0';
    tokens[*num_tokens].type = type;
    (*num_tokens)++;
    return len;
}

static inline int is_op_char(int c) {
    return c >= 0 && op_lookup[(unsigned char)c];
}

int tokenize(const char *input, Token_t *tokens, int *num_tokens) {
    *num_tokens = 0;

    for (int i = 0; input[i] != '\0'; ) {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (*num_tokens >= MAX_NUM_TOKENS) {
            return TOKEN_OVERFLOW;
        }

        int consumed = -1;

        if (isdigit(input[i])) {
            consumed = scan_and_emit(tokens, num_tokens, input, i, isdigit, NUM, TOKEN_STR_SIZE - 1);
        } else if (isalpha(input[i])) {
            consumed = scan_and_emit(tokens, num_tokens, input, i, isalpha, SYM, TOKEN_STR_SIZE - 1);
        } else if (is_op_char(input[i])) {
            consumed = scan_and_emit(tokens, num_tokens, input, i, is_op_char, OP, 1);
        }

        if (consumed <= 0) {
            return TOKEN_INVALID_CHAR;
        }

        i += consumed;
    }

    return 0;
}