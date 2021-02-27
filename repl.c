#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "mpc.h"

// lval related shenanigans

enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

typedef struct {
    int type;
    long num;
    int err;
} lval;


lval eval_op(lval x, char* op, lval y);
lval eval(mpc_ast_t* t);
void lval_println(lval v); 
void lval_print(lval v);
lval lval_err(int e);
lval lval_num(long x);


lval lval_num(long x){
    lval v;
    v.type = LVAL_NUM;
    v.num = x;
    return v;
}

lval lval_err(int e){
    lval v;
    v.type = LVAL_ERR;
    v.err = e;
    return v;
}

void lval_print(lval v){
    switch(v.type){
        case LVAL_NUM:
            printf("%li", v.num);
            break;
        case LVAL_ERR:
            if(v.err == LERR_DIV_ZERO){
                printf("Error: division by zero");
                break;
            }
            if(v.err == LERR_BAD_OP){
                printf("Error: operator not supported");
                break;
            }
            if(v.err == LERR_BAD_NUM){
                printf("Error: bad number");
                break;
            }
            break;
    }
}

void lval_println(lval v){ 
    lval_print(v); 
    putchar('\n'); 
}

// eval stuff 
lval eval(mpc_ast_t* t){

    if(strstr(t->tag, "number")){
        errno = 0;
        long x = strtol(t->contents, NULL, 10);
        if(errno == ERANGE){
            return lval_err(LERR_BAD_NUM);
        }
        return lval_num(x);
    }

    char* op = t->children[1]->contents;
    lval x = eval(t->children[2]);

    int i = 3;
    while(strstr(t->children[i]->tag, "expr")){
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}


lval eval_op(lval x, char* op, lval y){
    
    // check if error 
    if(x.type == LVAL_ERR){
        return x;
    }
     if(y.type == LVAL_ERR){
        return y;
    }
       

    if(strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
    if(strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
    if(strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
    if(strcmp(op, "/") == 0) { 
        if(y.num == 0){
            return lval_err(LERR_DIV_ZERO);
        return lval_num(x.num / y.num); 
        }
    }
    return lval_err(LERR_BAD_OP);
}

// main 

int main(int argc, char** argv){

    // some parsers
    mpc_parser_t* Num = mpc_new("number");
    mpc_parser_t* Op = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Prog = mpc_new("prog");

    // our grammar
    mpca_lang(MPCA_LANG_DEFAULT,
            "								\
            number 		: /-?[0-9]+/ ; 					\
            operator 	: '+' | '-' | '/' | '*' ; 			\
            expr 		: <number> | '(' <operator> <expr>+ ')' ; 	\
            prog 		: /^/ <operator> <expr>+ /$/ ;			\
            ",
            Num, Op, Expr, Prog);

    while(1){
        char* input = readline("> ");

        // grab input from stdin
        add_history(input);

        // parse input into AST	
        mpc_result_t r;

        if(mpc_parse("<stdin>", input, Prog, &r)){
            //mpc_ast_print(r.output);
            //printf("%li\n", eval(r.output));
            lval result = eval(r.output);
            lval_println(result);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }
    mpc_cleanup(4, Num, Op, Expr, Prog);
    return(0);
}
