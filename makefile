parser: parse.c minstack.c expr.c
	gcc -std=c99 -Wall parse.c minstack.c expr.c -o parse.out

expr: expr.c
	gcc -std=c99 -Wall expr.c -o expr.out

