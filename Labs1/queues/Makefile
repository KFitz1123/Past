







Third: Third.o arrayqueue.o
	clang -o Third Third.o arrayqueue.o

Third.o: Third.c arrayqueue.h
	clang -c Third.c

arrayqueue.o: arrayqueue.c arrayqueue.h
	clang -c arrayqueue.c



ListThird: ListThird.o Listqueue.o
	clang -o ListThird ListThird.o Listqueue.o

ListThird.o: ListThird.c Listqueue.h
	clang -c ListThird.c

Listqueue.o: Listqueue.c Listqueue.h
	clang -c Listqueue.c
