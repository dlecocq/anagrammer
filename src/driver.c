#include "anagram.h"

#include <stdio.h>
#include <stdlib.h>

int count = 0;

void cb(const char * str, unsigned int len, void * data) {
	//printf("Found: %s\n", str);
    count += 1;
}

int main() {
	anagram_node root;
	initialize_node(&root, NULL);
	
	loadFile(&root, "wordsEn.txt");
	
	anagrams(&root, "asdwtribnowplfglewhqagnbe", 4, cb, NULL);
    printf("Found: %i anagrams\n", count);
	
    // insert(&root, "hello");
    // anagrams(&root, "hello", 5, cb, NULL);
	
    destruct_node(&root);
	return 0;
}