#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for now, atoms are strings or numbers
typedef enum atom_t{
	NUM, STR
} atom_t;

typedef struct Atom {
	atom_t type;
	union {
		int num;
		char *str;
	};
} Atom;

// an expression can either consist of a list or an atom
typedef enum expr_t{
	LIST, ATOM, NIL, ROOT
}expr_t;

typedef struct List {
	expr_t type;
	union {
		Atom *data;
		struct List *head;
	};
	struct List *tail;
} List;

//---------------------

Atom * str_atom(char * s){
	Atom *a = malloc(sizeof(Atom));
	a->type = STR;
	a->str = s;
	return a;
}

Atom * num_atom(int n){
	Atom *a = malloc(sizeof(Atom));
	a->type = NUM;
	a->num = n;
	return a;
}

List * empty_list(){
	List * l = malloc(sizeof(List));
	l->type = NIL;
	l->head = NULL;
	l->tail = NULL;
	return l;
}

List * root_node(){
	List * root = empty_list();
	root->type = ROOT;
	return root;
}


List * create_atomic_list(char* sym){
	Atom *a;
	List *l = empty_list();
	l->type = ATOM;
	a = str_atom(sym);
	l->data = a;
	return l;
}


void print_atom(Atom *a){
	printf("%s ", a->str);
}


void append_list(List *car, List *cdr){
	if(cdr->type == ATOM){
		//printf("%s ", cdr->data->str);
	}
	if(car->type == ROOT){
		car->head = cdr;
		return;

	} else if(car->type == NIL){

		car->type = LIST;
		car->head = cdr;
		return;

	} else if (car->type == ATOM) {
		car->type = LIST;
		car->head = create_atomic_list(car->data->str);
		car->tail = cdr;
		return;

	} else if (car->type == LIST) {
		if(car->head == NULL){ // this really shouldn't happen...
			car->head = cdr;
			return;
		} else if (car->tail == NULL){ 
			car->tail = cdr;
			return;
		} else {
			append_list(car->tail, cdr);
		
		}
	} else {
		return;
	}	
}

void recur_print(List *l){
	if(l == NULL){
		return;
	}
	if(l->type == NIL){
		printf("( ) ");

	} else if(l->type == ATOM){
		print_atom(l->data);

	} else if(l->type == LIST){
		printf("( ");
		if(l->head != NULL){
			recur_print(l->head);
		}
		if(l->tail != NULL){
			recur_print(l->tail);
		}
		printf(") ");
	

	} else if(l->type == ROOT){
		printf("{ ");
		recur_print(l->head);
		printf("} ");
	}
}

void print_list_type(List *l){
	switch(l->type){
		case NIL: printf("NIL: "); break;
		case ROOT: printf("ROOT: "); break;
		case LIST: printf("LIST: "); break;
		case ATOM: printf("ATOM: "); break;
	}
}

