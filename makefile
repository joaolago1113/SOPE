CC= gcc
CFLAGS= -std=c11 -Wall -I"headers"

#aqui os ficheiros a compilar
FILES=strings
HEADERS=common_syscalls.h  strings.h  syscalls.h

SOURCES= $(foreach file, $(FILES), src/$(file).c )
OBJECTS= $(foreach file, $(FILES), $(file).o )
HEADERS_PATHS= $(foreach file, $(HEADERS), headers/$(file) )

TEST_LIBS = googletest/bins/gtest_main.a -lpthread
TEST_FLAGS = -I"headers" -I"googletest/include" -std=gnu++11 

find: $(SOURCES) $(HEADERS_PATHS) src/main.c
	$(CC) $(CFLAGS) $(SOURCES)  src/main.c -o find

test: $(SOURCES) $(HEADERS_PATHS) src/unit_tests.cpp
	$(CC) $(CFLAGS) $(SOURCES) -c
	g++ $(TEST_FLAGS)  $(OBJECTS) src/unit_tests.cpp  -o test $(TEST_LIBS) 
	rm *.o -f

clean:
	rm find -f
	rm test -f


