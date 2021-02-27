repl:	repl.c mpc.c
	gcc -std=c99 -Wall repl.c mpc.c -ledit -o repl 

lx:		lx.c
	gcc -std=c99 -Wall lx.c -o lx
