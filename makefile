is_valid_line:  is_valid_line.o identify.o
	gcc -Wall -ansi -pedantic  is_valid_line.o identify.o -o is_valid_line
is_valid_line.o: is_valid_line.c identify.c is_valid_line.h
	gcc -c -ansi -Wall -pedantic is_valid_line.c -o is_valid_line.o
identify.o: identify.c
	gcc -c -Wall -ansi -pedantic identify.c -o identify.o

                                                                  
