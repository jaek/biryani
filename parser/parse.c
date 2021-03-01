#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

typedef enum node_t{
    ATOM, LIST, NIL
} node_t;

typedef enum atom_t {
    NUM, STR, OP, SYM
} atom_t;

struct Atom; //a number or a symbol
struct Node; //a lisp expression 
typedef struct Node * list; 

typedef union atom_d{
    int num;
    char* str;
    char op;
    char* sym;
}atom_d;

struct Atom { 
    atom_t type;
    atom_d data;
} Atom;

struct Node {
    enum node_t type;
    struct Node *parent;
    union { // a node can either be a list or an atom
        struct Atom *atom;
        list car;
    };
    list cdr;
} Node;

list new_node(){
    list l = malloc(sizeof(list));
    l->type = NIL;
    return l;
}

list new_list_node(){
    list l = new_node();
    l->type = LIST;
    l->car = NULL;
    l->cdr = NULL;
    return l;
}

void create_str_node(char *s, list n){
    struct Atom *atom = malloc(sizeof(struct Atom));
    atom->type = STR;
    atom->data.str = s;
    n->type = ATOM;
    n->atom = atom;
}

struct parser{
    struct lex_r *lx;
    int curr_tok;
    list head;
    list curr;
} parser;


void init_parser(struct parser *p){
    p->curr_tok = -1;
    p->lx = NULL;
    p->head = NULL;
}

char *curr_tok(struct parser *p){
    return p->lx->rep[p->curr_tok];
}

char *peek_tok(struct parser *p){
    char* err = "\0";
    if((p->curr_tok + 1) < p->lx->count){
        return p->lx->rep[p->curr_tok+ 1];
    } else {
        return err; 
    }
}

int next_tok(struct parser *p){
    int n = p->curr_tok + 1;
    if(n >= p->lx->count){
        return -1;
    }
    p->curr_tok = n;
    return n;
}

int is_int(char *s){
    int z=0;
    for(int i=0; i<strlen(s); i++){
        if(s[i] >= '0' && s[i] <= '9'){
            z *= 10;
            z += s[i] - 48;
        } else {
            return -1;
        }
    }
    return z;
}

list parse_expr(struct parser *p, list curr){
    
    while(next_tok(p) != -1){
        char *tok = curr_tok(p);
        printf("%i %s\n", p->curr_tok, tok);
        
        
        if(tok[0] == '('){
            //TODO: initialize parser with NIL startnode
            //change NIL node type to contain expr
            if(curr->type == NIL){
                curr->type = LIST;
                curr->car = new_node();
                curr->cdr = NULL;
                parse_expr(p, curr->car);
            } else if(p->curr->type == LIST){  
                curr->cdr = new_node();
                parse_expr(p, curr->cdr);
                
            } else if(p->curr->type == ATOM){ // must be an atom
                curr->type = LIST;
                curr->cdr = new_node();
                parse_expr(p, curr->cdr);
            }
        } else if(tok[0] == ')'){
            return curr;
        } else {
            
            
            if(curr->type == NIL){
                create_str_node(tok, curr);
            } else if(curr->type == LIST){
                create_str_node(tok, curr->cdr);
            } else {
                curr->type = LIST;
                curr->cdr = new_node();
            }
        } 
    }
    //TODO: handle operators
    print_list(p->head);
    return p->head;
}

void print_list(list h){
    if(h->type == NIL){
        printf("NIL\n");
    } else if(h->type == LIST){
        printf("LIST\n"); 
        if(h->car != NULL){
            print_list(h->car);
        }
        if(h->cdr != NULL){
            print_list(h->cdr);
        }
    }
        
    else if(h->type == ATOM){
        printf("ATOM: %s\n", h->atom->data.str);
    }
    
}

void parse_input(char *input, struct parser *p){
    p->lx = tokenize(input);
    p->curr = p->head = new_node();
    show_lex(p->lx);
    parse_expr(p, p->curr);
}


int main(int argc, char** argv){
    char input[2048];
    struct parser p;
    while(1){
        init_parser(&p);
        printf(">>> ");
        fgets(input, 2048, stdin);
        parse_input(input, &p);
    }
    return 0;
}
