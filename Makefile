homo : main.o enc.o keygen.o utils.o
	gcc main.o enc.o keygen.o utils.o\
		-L. -lpbc -lgmp -std=c99 -o homo 

main.o : main.c enc.h keygen.h utils.h
	gcc -c main.c
enc.o: enc.c enc.h keygen.h
	gcc -c enc.c
keygen.o : keygen.c keygen.h utils.h
	gcc -c keygen.c
utils.o : utils.c utils.h
	gcc -c utils.c
clean :
	rm homo *.o
