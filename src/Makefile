CC     = gcc
CCOPTS = -O3 -Wall -g

LD     = gcc
LDOPTS = 

all: driver buildTest

driver: anagram.o driver.c
	$(CC) $(CCOPTS) driver.c -o driver anagram.o

buildTest: test/test.c anagram.o
	$(CC) $(CCOPTS) test/test.c -o test/test anagram.o

test: buildTest
	@(cd test; ./test)

anagram.o: anagram.h anagram.c
	$(CC) $(CCOPTS) -c anagram.c -o anagram.o

clean:
	rm -f *.o driver test/test