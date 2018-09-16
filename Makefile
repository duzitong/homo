homo : main.o utils.o
	gcc main.o utils.o\
		-L. -lpbc -lgmp -std=c99 -o homo 

main.o : main.c utils.h
	gcc -c main.c
utils.o : utils.c utils.h
	gcc -c utils.c
clean :
	rm homo *.o
