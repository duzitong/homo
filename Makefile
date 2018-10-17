homo : main.o verify.o compute.o enc.o keygen.o utils.o
	gcc main.o verify.o compute.o enc.o keygen.o utils.o \
		-L. -lpbc -lgmp -std=c99 -o homo 

main.o : main.c verify.h compute.h enc.h keygen.h utils.h
	gcc -c main.c
verify.o: verify.c verify.h compute.h enc.h keygen.h
	gcc -c verify.c
compute.o: compute.c compute.h enc.h keygen.h
	gcc -c compute.c
enc.o: enc.c enc.h keygen.h
	gcc -c enc.c
keygen.o : keygen.c keygen.h utils.h
	gcc -c keygen.c
kangaroo.o: kangaroo.c kangaroo.h
	gcc -c kangaroo.c
utils.o : utils.c utils.h
	gcc -c utils.c

test: test.o kangaroo.o utils.o
	gcc test.o kangaroo.o utils.o\
		-L. -lpbc -lgmp -std=c99 -o test 
test.o: test.c
	gcc -c test.c

gen: prime.c
	gcc prime.c -L. -lpbc -lgmp -o gen

clean :
	rm homo test gen *.o
