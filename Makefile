analyse: get_programme.o fonctions.o mat.o brin.o main.o
	gcc -o analyse get_programme.o fonctions.o mat.o brin.o main.o

get_programme.o: get_programme.c
	gcc -o get_programme.o -c get_programme.c

fonctions.o: fonctions.c
	gcc -o fonctions.o -c fonctions.c

mat.o: mat.c
	gcc -o mat.o -c mat.c

brin.o: brin.c
	gcc -o brin.o -c brin.c

main.o: main.c
	gcc -o main.o -c main.c


clean:
	rm *.o
