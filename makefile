parse: lexer.h parse.c
	gcc -std=c99 -Wall parse.c -o parse

repl:	repl.c mpc.c
	gcc -std=c99 -Wall repl.c mpc.c -ledit -o repl 



