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
		
	printf("Found %i\n", anagrams(&root, "olelh", cb, NULL));
	
	return 0;
}