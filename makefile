CC=gcc
CFLAGS=-Wall -Werror -I.
DEPS=is_valid_line.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

is_valid_line: is_valid_line.o identify.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o is_valid_line

