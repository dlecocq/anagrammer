/* Unit tests */

#include "minunit.h"
#include "../anagram.h"

#include <stdio.h>

int tests_run = 0;

static char * test_insert_contains() {
	anagram_node root;
	initialize_node(&root, NULL);
	mu_assert("Doesn't contain before insertion", !contains(&root, "hello"));
	insert(&root, "hello");
	mu_assert("Contains after insertion", contains(&root, "hello"));
	destruct_node(&root);
	return 0;
}

static char * test_insert_multiple() {
	anagram_node root;
	initialize_node(&root, NULL);
	insert(&root, "hello");
	insert(&root, "hell");
	insert(&root, "he");
	mu_assert("Contains multiple", contains(&root, "hello") && contains(&root, "hell") && contains(&root, "he"));
	destruct_node(&root);
	return 0;
}

void noop(const char * str, unsigned int len, void * data) {}
static char * test_anagrams() {
	anagram_node root;
	initialize_node(&root, NULL);
	insert(&root, "hello");
	insert(&root, "hell");
	insert(&root, "he");
	mu_assert("Finds anagrams", anagrams(&root, "hello", noop, NULL) == 3);
	destruct_node(&root);
	return 0;
}

static char * test_leaf() {
	anagram_node root;
	initialize_node(&root, NULL);
	mu_assert("Empty node is leaf", leaf(&root));
	insert(&root, "hello");
	mu_assert("Full node is not leaf", !leaf(&root));
	destruct_node(&root);
	return 0;
}

static char * test_delete() {
	anagram_node root;
	initialize_node(&root, NULL);
	mu_assert("Empty node is leaf", leaf(&root));
	insert(&root, "hello");
	mu_assert("Full node is not leaf", !leaf(&root));
	del(&root, "hello");
	mu_assert("Deleted node is leaf", leaf(&root));
	destruct_node(&root);
	return 0;
}

// Make sure we never report duplicates in anagram searches
static char * test_duplicates() {
	anagram_node root;
	initialize_node(&root, NULL);
	insert(&root, "hello");
	mu_assert("Exactly one anagram found when sorted", anagrams(&root, "ehllo", noop, NULL) == 1);
	mu_assert("Exactly one anagram found when unsorted", anagrams(&root, "lehlo", noop, NULL) == 1);
	mu_assert("Exactly one anagram found when reversed", anagrams(&root, "ollhe", noop, NULL) == 1);
	destruct_node(&root);
	return 0;
}

// Make sure that we can correctly read from a file
static char * test_loadFile() {
	anagram_node root;
	initialize_node(&root, NULL);
	loadFile(&root, "test-dictionary.txt");
	mu_assert("Found 'spot' in dictionary", contains(&root, "spot"));
	mu_assert("Found 'your' in dictionary", contains(&root, "your"));
	mu_assert("Found 'name' in dictionary", contains(&root, "name"));
	destruct_node(&root);
	return 0;
}

static char * all_tests() {
	mu_run_test(test_insert_contains);
	mu_run_test(test_insert_multiple);
	mu_run_test(test_anagrams);
	mu_run_test(test_leaf);
	mu_run_test(test_delete);
	mu_run_test(test_duplicates);
	mu_run_test(test_loadFile);
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