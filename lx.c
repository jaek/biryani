#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 100


// take  a str and return a char** consisting of tokens. final elem in array is '\0'
char** tokenize(char* s){
    char** o;
    o = malloc(sizeof(char*)*BUFFER_LEN); 
    int i = 0, j = 0, k; //i - input string[i], j - out array o[j]
    while(s[i] != '\0'){
        if(i == BUFFER_LEN){
            fprintf(stderr, "tokenize: input str too long\n");
        if(s[i] == ' '){
            ; //ignore spaces
        } else if((s[i] >= '(' && s[i] <= '+') || s[i] == '-' || s[i] == '/'){ //handle operators +-/* and ()
            o[j] = malloc(sizeof(s[i]) + 1); 
            o[j][0] = s[i];
            o[j][1] = '\0';
            j++;
        } else { // treat as an identifier for now
            k = i+1;
            while(s[k] != ' ' && s[k] != '(' && s[k] != ')'){
                k++; 
            }
            o[j] = malloc((sizeof(char) * (k - i)) + 2);
            k = 0;
            while(s[i] != ' ' && s[i] != '(' && s[i] != ')'){
                o[j][k] = s[i];
                i++;
                k++; 
            }
            o[j][k] = '\0';
            j++;
        }
        i++;
        o[j] = malloc(sizeof(char));
        o[j][0] = '\0';
    }
    return o; 
}

typedef struct lex_r {
    char** rep;
    int len;
} lex_r;

int get_len(char** c){
    int i = 0;
    while(c[i][0] != '\0'){
        i++;
    }
    return i;
}

int main(int argc, char** argv){
    char* l = "(print '1+2=' (+ 1 2))";
    char** a = tokenize(l);
    while(**a != '\0'){
        printf("%s", *a);
        a++;
    } 
    lex_r lx;
    lx.rep = tokenize(l);
    lx.len = get_len(lx.rep);
    printf("%i\n", lx.len);
    return 0;
}
