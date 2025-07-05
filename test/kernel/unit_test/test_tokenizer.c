#include <stdio.h>
#include <string.h>
#include <kernel/tokenization.h>

void println_token(const Token_t *token, const int i) {
    printf("%s\t", token->tokn[i]);

    switch (token->type[i]) {
        case NUM:   printf("number");           break;
        case SYM:   printf("symbolic");         break;
        case OPR:   printf("operator");         break;
        case PRT:   printf("parenthese");       break;
        default:    printf("unknown");          break;
    }
    printf("\n");
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

        Token_t *tokens = create_tokens();
        
        for (int i = 0; i < 1000000; ++i) {
            tokenize(tokens, line);
        }
        printf("Parsed %d tokens:\n", tokens->ntok);
        for (int i = 0; i < MAXNTOK; i++) {
            println_token(tokens, i);
        }
        printf("\n\n");
        free_tokens(tokens);
    }

    fclose(fp);
    return 0;
}
