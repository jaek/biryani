#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "minstack.h"


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
	sym[len+1] = '\0';
	printf("new sym: %s\n", sym);
	return sym;
}

int parse_expr(char * c,  int i, Top t){
	int end;
	List *n;
	char *sym;
	switch(c[i]){
		case ' ':
			return parse_expr(c, i+1, t);
		case ')':
			return (bs_pop(&t) == ')') ? parse_expr(c, i+1, t) : -1;
		case '(':
			n = empty_list();
			if(bs_peek(t) != NULL){
				printf("appending new empty list\n");
				append_list(bs_peek(t), n);
			}
			bs_push(n, ')', &t);
			return parse_expr(c, i+1, t);
		case '\0':
			printf("EOF\n");
			return (t->count == 0) ?  1 : -1;
		default:
			printf("default\n");
			//create a new symbol
			end = next_terminal(c, i);
			printf("end: %i\n", c[end]);
			sym = get_symbol(c, i, end);
			//add it to the env
			n = create_atomic_list(sym);

			printf("appending new atomic list %s\n", sym);
			append_list(bs_peek(t), n);	
			return parse_expr(c, end, t);
	}
}

void repl(){
	char input[2048];
	while(1){

		printf("\ninput> ");
		scanf("%s", input);
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
	repl();
	return 0;
}
