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
		Atom * data;
		struct List *head;
	};
	struct List *tail;
} List;

List * empty_list();

List * root_node();

Atom * str_atom(char * s);

Atom * num_atom(int n);

List * create_atomic_list(char* sym);

void append_list(List *car, List *cdr);

int is_int(char *);

void recur_print(List *l);

void print_atom(Atom *a);

void list_print(List *l);

void print_list_type(List *l);
