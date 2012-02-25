#include "anagram.h"

#include <stdio.h>
#include <stdlib.h>

void cb(const char * str, unsigned int len) {
	printf("Found: %s\n", str);
}

int main() {
	anagram_node root;
	initialize_node(&root, NULL);
	
	insert(&root, "hello");
		
	printf("Found %i\n", anagrams(&root, "ollhe", cb));
	
	return 0;
}