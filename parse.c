#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

typedef enum node_t{
    ATOM, PAIR, NIL
} node_t;

typedef enum atom_t{
    NUM, STR, OP
} atom_t;

typedef struct atom{
    atom_t type;
    union atom_d{
        int num;
        char* str;
        char* op;
    } data;
} atom;

typedef struct node{
    enum node_t type;
    struct atom *data;
    struct node *head;
    struct node *tail; 
} node;

node *new_node(){
    struct node *n = malloc(sizeof(struct node));
    n->type = NIL;
    return n;
}

node *parser(char *s){
    node *head = new_node();
    lex_r *lx = tokenize(s);
    return head;
}

int main(int argc, char** argv){


    while(1){
        char* input = readline("> ");
    }

    return 0;
}
