#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

void println_token(const Token_t *token) {
    printf("%s\n", token->text);
}

void print_token(const Token_t *token) {
    printf("%s", token->text);
}

int main() {
    FILE *fp = fopen("../expressions.txt", "r");
    if (!fp) {
        perror("Error opening expressions.txt");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0') continue;

        printf("%s\n", line);

        Token_t tokens[MAX_NUM_TOKENS];
        int num_tokens = 0;

        int result = tokenize(line, tokens, &num_tokens);

        if (result < 0) {
            if (result == TOKEN_INVALID_CHAR) {
                printf("Error: Invalid character in input.\n");
            } else if (result == TOKEN_OVERFLOW) {
                printf("Error: Too many tokens.\n");
            } else {
                printf("Unknown error: %d\n", result);
            }
            continue;
        }

        printf("Parsed %d tokens:\n", num_tokens);
        for (int i = 0; i < num_tokens; ++i) {
            println_token(&tokens[i]);
        } for (int i = 0; i < num_tokens; ++i) {
            print_token(&tokens[i]);
        }
        printf("\n\n");
    }

    fclose(fp);
    return 0;
}