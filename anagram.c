#include "anagram.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This is the base character code we'll subtract off of 
 * every input string when determining its index into nodes,
 * and how much we'll add back when reconstructing the 
 * string. */
const unsigned int base = 97;

int __comparator(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void initialize_node(anagram_node * node, anagram_node * parent) {
	unsigned int i = 0;
	for (i = 0; i < 26; ++i) {
		node->nodes[i] = NULL;
	}
	node->parent = parent;
	node->valid  = 0;
}

void destruct_node(anagram_node * node) {
	unsigned int i = 0;
	for (i = 0; i < 26; ++i) {
		if (node->nodes[i] != NULL) {
			destruct_node(node->nodes[i]);
			free(node->nodes[i]);
			node->nodes[i] = NULL;
		}
	}
}

int leaf(const anagram_node * node) {
	unsigned int sum = 0, index = 0;
	for (index = 0; index < 26; ++index) {
		sum += (node->nodes[index] != NULL);
	}
	return sum == 0;
}

anagram_node * insert(anagram_node * node, const char * str) {
	return _insert(node, str, strlen(str));
}

anagram_node * _insert(anagram_node * node, const char * str, unsigned int len) {
	if (len == 0) {
		node->valid = 1;
		return node;
	} else {
		unsigned int index = (unsigned int)(str[0]) - base;
		if (node->nodes[index] == NULL) {
			node->nodes[index] = (anagram_node*)(malloc(sizeof(anagram_node)));
			initialize_node(node->nodes[index], node);
		}
		if (len == 1) {
			return _insert(node->nodes[index], NULL, 0);
		} else {
			return _insert(node->nodes[index], (const char*)(&str[1]), len-1);
		}
	}
}

void delete(anagram_node * node, const char * str) {
	return _delete(node, str, strlen(str));
}

void _delete(anagram_node * node, const char * str, unsigned int len) {
	if (len == 0) {
		node->valid = 0;
	} else {
		unsigned int index = (unsigned int)(str[0]) - base;
		if (node->nodes[index] == NULL) {
			return;
		} else {
			if (len == 1) {
				_delete(node->nodes[index], NULL, len-1);
			} else {
				_delete(node->nodes[index], (const char*)(&str[1]), len-1);
			}
			/* After we've deleted from the subtrees, we should 
			 * see if the node we just deleted was a leaf. If so,
			 * we can prune this one! */
			if (leaf(node->nodes[index])) {
				free(node->nodes[index]);
				node->nodes[index] = NULL;
			}
		}
	}
}

int contains(anagram_node * node, const char * str) {
	return _contains(node, str, strlen(str));
}

int _contains(anagram_node * node, const char * str, unsigned int len) {
	if (len == 0) {
		return node->valid;
	} else {
		unsigned int index = (unsigned int)(str[0]) - base;
		if (node->nodes[index] == NULL) {
			return 0;
		} else if (len == 1) {
			return _contains(node->nodes[index], NULL, 0);
		} else {
			return _contains(node->nodes[index], (const char*)(&str[1]), len-1);
		}
	}
}

unsigned int anagrams(anagram_node * node, const char * str, found_callback cb) {
	unsigned int len = strlen(str);
	// Make a copy of the string that we can modify, and then sort it
	char * _str = (char*)(malloc(len));
	memcpy(_str, str, len);
	qsort(_str, len, sizeof(char), __comparator);
	// Make a buffer where we'll store the string
	char * _buf = (char*)(malloc(len + 1));
	// Return
	return _anagrams(node, _str, len, _buf, 0, cb);
}

unsigned int _anagrams(anagram_node * node,
		char * str, unsigned int len,
		char * buf, unsigned int buf_len,
		found_callback cb) {
	if (len == 0) {
		buf[buf_len+1] = 0;
		cb(buf, buf_len);
		return node->valid;
	} else {
		char         tmp   = 'a';
		unsigned int sum   = 0;
		unsigned int count = 0;
		unsigned int index = 0;
		
		if (node->valid) {
			buf[buf_len+1] = 0;
			cb(buf, buf_len);
			sum += 1;
		}
		
		// Loop through each of the letters and search there.
		for (count = 0; count < len; ++count) {
			// If this letter is a repeat of the last letter, skip it
			if (count && str[count] == str[count-1]) {
				continue;
			} else {
				/* Otherwise, swap the current letter with the first one,
				 * then return anagrams, and then unswap them */
				index = (unsigned int)(str[count]) - base;
				if (node->nodes[index] != NULL) {
					// Save for later
					tmp = str[count];
					str[count] = str[0];
					// Add this character to the buffer
					buf[buf_len] = tmp;
					// Find any sub-anagrams
					sum += _anagrams(node->nodes[index], (char*)(&str[1]), len-1, buf, buf_len + 1, cb);
					// Unswap
					str[count] = tmp;
				}
			}
		}
		return sum;
	}
}