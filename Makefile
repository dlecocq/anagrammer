CC     = gcc
CCOPTS = -O3 -Wall -g

LD     = gcc
LDOPTS = 

all: driver

driver: anagram.o driver.c
	$(CC) $(CCOPTS) driver.c -o driver anagram.o

test: test.c anagram.o
	$(CC) $(CCOPTS) test.c -o test anagram.o

anagram.o: anagram.h anagram.c
	$(CC) $(CCOPTS) -c anagram.c -o anagram.o

clean:
	rm -f *.o driver