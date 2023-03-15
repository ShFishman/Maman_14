is_valid_line: is_valid_line.o identify.o table.o
	gcc -Wall -ansi -pedantic is_valid_line.o identify.o table.o -o is_valid_line

is_valid_line.o: is_valid_line.c is_valid_line.h
	gcc -c -ansi -Wall -pedantic is_valid_line.c -o is_valid_line.o

identify.o: identify.c identify.h table.h
	gcc -c -Wall -ansi -pedantic identify.c -o identify.o

table.o: table.c table.h
	gcc -c -Wall -ansi -pedantic table.c -o table.o
                                                                 
