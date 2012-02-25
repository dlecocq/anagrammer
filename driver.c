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
	insert(&root, "he");
	insert(&root, "hell");
	
	if (contains(&root, "hello")) {
		printf("Contains hello.\n");
	} else {
		printf("Does not contain hello.\n");
	}
	
	printf("Found %i\n", anagrams(&root, "hello", cb));
	
	return 0;
}