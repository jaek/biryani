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

// Return the integer offest of the next terminal character
int next_terminal(char *input_string, int offset){
	int i = offset;
	while(is_terminal(input_string[i]) == false){
		i++;
	}
	return i;
}

// given a start offset and an end offset, return a new null-terminated string
char *get_symbol(char *c, int start, int end){
	int len = (end - start);
	char * sym  = malloc(sizeof(char) * len + 1);
	memcpy(sym, &c[start], len);
	sym[len+1] = '\0';
	return sym;
}



int parse_expr(char * input,  int offset, Top t){
	int end;
	List *new_symbol;
	char *sym;

	switch(input[offset]){
		case '\n': 
		case ' ':
			return parse_expr(input, offset+1, t); // ignore newlines and spaces in parsing the input
		case ')':
			return (bs_pop(&t) == ')') ? parse_expr(input, offset+1, t) : -1;
		case '(':
			new_symbol = empty_list();
			append_list(bs_peek(t), new_symbol);
			bs_push(new_symbol, ')', &t);
			return parse_expr(input, offset+1, t);
		case '\0':
			return (t->count == 0) ?  1 : -1;
		default:
			//create a new symbol
			end = next_terminal(input, offset);
			sym = get_symbol(input, offset, end);
			//add it to the env
			new_symbol = create_atomic_list(sym);
			if(bs_peek(t) == NULL){
				printf("error: NULL head\n");
			} else { 
				append_list(bs_peek(t), new_symbol);	
			}
			return parse_expr(input, end, t);
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
		//list_print(root);
		free_stack(t);
	}
}

int main(int argv, char** argc){

	//_test_parser();
	//_test_list_operations();
	repl();
	return 0;
}
