#include <stdio.h>
#include <stdlib.h>

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
	return n;
}

int main(int argc, char** argv){
	return 0;
}
