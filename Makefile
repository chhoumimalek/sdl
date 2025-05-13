
prog : main.o person.o
	gcc main.o person.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
	
main.o: main.c
	gcc -c main.c -g  

person.o: person.c
	gcc -c person.c -g  

