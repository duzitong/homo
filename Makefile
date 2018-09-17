homo : main.o keygen.o utils.o
	gcc main.o keygen.o utils.o\
		-L. -lpbc -lgmp -std=c99 -o homo 

main.o : main.c keygen.h utils.h
	gcc -c main.c
keygen.o : keygen.c keygen.h
	gcc -c keygen.c
utils.o : utils.c utils.h
	gcc -c utils.c
clean :
	rm homo *.o
