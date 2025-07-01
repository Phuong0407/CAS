#include <stdio.h>
#include <string.h>
#include <kernel/tokenization.h>

void println_token(const Token_t *token) {
    printf("%s\t", token->tokn);

    switch (token->type) {
        case NUM:   printf("number");           break;
        case SYM:   printf("symbolic");         break;
        case OPR:   printf("operator");         break;
        case PRT:   printf("parenthese");       break;
        default:    printf("unknown");          break;
    }
    printf("\n");
}


void print_token(const Token_t *token) {
    printf("%s", token->tokn);
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
        
        if (line[0] == '\0')
            continue;
        
        printf("%s\n", line);

        Token_t tokens[MAXNTOK];
        int num_tokens = 0;

        for (int i = 0; i < 1000000; ++i)
            tokenize(tokens, line, &num_tokens);
        printf("Parsed %d tokens:\n", num_tokens);
        for (int i = 0; i < num_tokens; ++i) {
            println_token(&tokens[i]);
        }
        printf("\n\n");
    }

    fclose(fp);
    return 0;
}