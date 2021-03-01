#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKENS 128 

typedef struct lex_r {
    char* rep[MAX_TOKENS];
    int count; //number of tokens
} lex_r;

// take  a str and return a char** consisting of tokens. final elem in array is '\0'
lex_r* tokenize(char* s){
    lex_r *lx = malloc(sizeof(lex_r));
    // list of tokens
    int i = 0, k; //i - input string[i], j - out array o[j]
    int tok = 0;
    while(s[i] != '\0'){
        if(i == MAX_TOKENS){
            fprintf(stderr, "tokenize: input str too long\n");
        }
        // TODO: refactor to switch statement
        if(s[i] == ' '){
            ; //ignore spaces
        } else if((s[i] >= '(' && s[i] <= '+') || s[i] == '-' || s[i] == '/'){ //handle operators +-/* and ()
            lx->rep[tok] = malloc(sizeof(s[i]) + 1); 
            lx->rep[tok][0] = s[i];
            lx->rep[tok][1] = '\0';
            tok++;
        } else { // treat anything that isn't an operator or bracket as an identifier for now
            k = i+1;
            while(s[k] != ' ' && s[k] != '(' && s[k] != ')'){
                k++; 
            }
            lx->rep[tok] = malloc((sizeof(char) * (k - i)) + 2);
            k = 0;
            while(s[i] != ' ' && s[i] != '(' && s[i] != ')'){
                lx->rep[tok][k] = s[i];
                i++;
                k++; 
            }
            lx->rep[tok][k] = '\0';
            tok++;
        }
        i++;
    }
    lx->count = tok;
    return lx; 
}

void show_lex(lex_r *lx){
    printf("Number of tokens: %i\n", lx->count);
    for(int i=0; i<lx->count; i++){
        printf("%i: %s\n", i, lx->rep[i]);
    }
}

void free_lex(lex_r *lx){
    for(int i=0; i<lx->count; i++){
        #ifdef DEBUG 
        printf("Freeing: %i - %s\n", i, lx->rep[i]);
        #endif
        free(lx->rep[i]);
    }
    #ifdef DEBUG
    printf("Freeing lexer\n");
    #endif
    free(lx);
}

