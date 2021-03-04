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
	return sym;
}

int parse_expr(char * c,  int i, Top t){
	int end;
	List *n;
	char *sym;

	switch(c[i]){
		case '\n':
		case ' ':
			return parse_expr(c, i+1, t);
		case ')':
			return (bs_pop(&t) == ')') ? parse_expr(c, i+1, t) : -1;
		case '(':
			n = empty_list();
			append_list(bs_peek(t), n);
			bs_push(n, ')', &t);
			return parse_expr(c, i+1, t);
		case '\0':
			return (t->count == 0) ?  1 : -1;
		default:
			//create a new symbol
			end = next_terminal(c, i);
			sym = get_symbol(c, i, end);

			//add it to the env
			n = create_atomic_list(sym);
			if(bs_peek(t) == NULL){
				printf("error: NULL head\n");
			} else { 
				append_list(bs_peek(t), n);	
			}
			return parse_expr(c, end, t);
	}
}

void repl(){
	char input[2048];
	while(1){

		printf("\ninput> ");
		fgets(input, 2048, stdin);

		List *root  = root_node();
		Top t = bs_init(0);
		bs_push(root, '!', &t);

		parse_expr(input, 0, t);

		recur_print(root);
		free_stack(t);
	}
}

int main(int argv, char** argc){

	//_test_parser();
	//_test_list_operations();
	repl();
	return 0;
}
