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

List * empty_list();

Atom * str_atom(char * s);

Atom * num_atom(int n);

