CC= gcc
CFLAGS= -std=c11 -Wall

#aqui os ficheiros a compilar
FILES=string

SOURCES= $(foreach file, $(FILES), src/$(file).c )
OBJECTS= $(foreach file, $(FILES), bins/$(file).o )

find:
	$(CC) $(CFLAGS) $(SOURCES) src/main.c -o find

test:
	$(CC) $(CFLAGS) $(SOURCES) src/main.c -o find

clean:
	rm find -f
	rm test -f


