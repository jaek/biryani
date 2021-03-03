#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "minstack.h"
#include "expr.h"

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

bool is_terminal(char c){
	if(c == '(' || c == ')' || c == ' ' || c == '\0'){
		return true;
	} else {
		return false;
	}
}

int next_terminal(char *c, int start){
	int i = start;
	while(is_terminal(c[i]) == false){
		i++;
	}
	return i;
}

char *get_symbol(char *c, int start, int end){
	int len = (end - start);
	char * sym  = malloc(sizeof(char) * len + 1);
	memcpy(sym, &c[start], len);
	return sym;
}

int parse_expr(char * c,  int i, Top t){
	int end;
	char *sym;
	switch(c[i]){
		case ' ':
			return parse_expr(c, i+1, t);
		case ')':
			return (bs_pop(&t) == ')') ? parse_expr(c, i+1, t) : -1;
		case '(':
			bs_push(empty_list(), ')', &t);
			return parse_expr(c, i+1, t);
		case '\0':
			return (t->count == 0) ? 1 : -1;
		default:
			//create a new symbol
			end = next_terminal(c, i);
			sym = get_symbol(c, i, end);
			printf("new sym: %s\n", sym);
			return parse_expr(c, end, t);
	}
}

void repl(){
	char input[2048];
	while(1){

		printf("input> ");
		scanf("%s", ighhkput);
		Top t = bs_init(0);
		parse_expr(input, 0, t);
		free_stack(t);
	}
}

void _test_parser(){
	//next_terminal
	printf("testing next_terminal\n");
	int i = 0;
	char *s = "test) this out";
	printf("test str: %s\n", s);
	int end = next_terminal(s, i);
	printf("next_terminal i=5 : %i\n", next_terminal(s, 5));
	char * sym = get_symbol(s, i, end);
	printf("from index 0: %s\n", sym);
	//parse_expr
	char *test = "(test (t))";
	printf("test str: %s - len %li\n", test, strlen(test));
	Top t = bs_init(0);
	parse_expr(test, 0, t);

}


int main(int argv, char** argc){
	//repl();
	_test_parser();
	return 0;
}
