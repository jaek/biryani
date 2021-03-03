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
	LIST, ATOM, NIL
}expr_t;

typedef struct List {
	expr_t type;
	union {
		Atom * data;
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
	if(car->head == NULL){
		printf("append: nil\n");
		car->type = LIST;
		car->head = cdr;
		return;
	} else if (car->tail == NULL) {
		printf("append: tail == NULL\n");
		car->tail = cdr;
		return;
	} else {
		printf("append: tail !== NULL\n");
		append_list(car->tail, cdr);
		car->tail = cdr;
		return;
	}	
}

void print_atom(Atom *a){
	printf("A-> %s\n", a->str);
}

void recur_print(List *l){
	if(l == NULL){
		return;
	} else if(l->type == NIL){
		printf("NIL\n");
	} else if(l->type == ATOM){
		print_atom(l->data);
	} else {
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
	if(is_int(sym)){
		a = num_atom(is_int(sym));
	} else {
		a = str_atom(sym);
	}
	l->data = a;
	return l;
}
