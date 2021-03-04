#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//TODO: fix this
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

void append_list(List *car, List *cdr){
	if(car->type == NIL){
		car->type = LIST;
		car->head = cdr;
		return;
	} else if (car->type == ATOM || car->tail == NULL) {
		car->tail = cdr;
		return;
	} else {
		append_list(car->tail, cdr);
		return;
	}	
}

void print_atom(Atom *a){
	printf("Atom-> %s : %i\n", a->str, a->type);
}

void recur_print(List *l){
	if(l == NULL){
		printf("* NULL PRINT\n");
		return;
	} else if(l->type == NIL){
		printf("* NIL NODE\n");
	} else if(l->type == ATOM){
		printf("* ATOM NODE\n");
		print_atom(l->data);
	} else {
		if(l->type != ROOT){
		printf("* LIST NODE\n");
		}
		if(l->head != NULL){
			recur_print(l->head);
		}
		if(l->tail!= NULL){
			recur_print(l->tail);
		}
	}
}

List * create_atomic_list(char* sym){
	Atom *a;
	List *l = empty_list();
	l->type = ATOM;
	a = str_atom(sym);
	l->data = a;
	return l;
}

