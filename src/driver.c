#include "anagram.h"

#include <stdio.h>
#include <stdlib.h>

void cb(const char * str, unsigned int len, void * data) {
	printf("Found: %s\n", str);
}

int main() {
	anagram_node root;
	initialize_node(&root, NULL);
	
   insert(&root, "hello");
   anagrams(&root, "hello", 5, cb, NULL);
	
   destruct_node(&root);
	return 0;
}