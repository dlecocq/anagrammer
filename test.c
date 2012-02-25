/* Unit tests */

#include "minunit.h"
#include "anagram.h"

#include <stdio.h>

int tests_run = 0;

static char * test_insert_contains() {
	anagram_node root;
	initialize_node(&root, NULL);
	mu_assert("Doesn't contain before insertion", !contains(&root, "hello"));
	insert(&root, "hello");
	mu_assert("Contains after insertion", contains(&root, "hello"));
	return 0;
}

static char * test_insert_multiple() {
	anagram_node root;
	initialize_node(&root, NULL);
	insert(&root, "hello");
	insert(&root, "hell");
	insert(&root, "he");
	mu_assert("Contains multiple", contains(&root, "hello") && contains(&root, "hell") && contains(&root, "he"));
	return 0;
}

void noop(const char * str, unsigned int len) {}
static char * test_anagrams() {
	anagram_node root;
	initialize_node(&root, NULL);
	insert(&root, "hello");
	insert(&root, "hell");
	insert(&root, "he");
	mu_assert("Finds anagrams", anagrams(&root, "hello", noop) == 3);
	return 0;
}

static char * all_tests() {
	mu_run_test(test_insert_contains);
	mu_run_test(test_insert_multiple);
	mu_run_test(test_anagrams);
	return 0;
}

int main(int argc, char **argv) {
	char * result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	} else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
	return result != 0;
}