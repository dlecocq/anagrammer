#include "anagram.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* This is the base character code we'll subtract off of 
 * every input string when determining its index into nodes,
 * and how much we'll add back when reconstructing the 
 * string. */
const unsigned int base = 97;

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

void del(anagram_node * node, const char * str) {
	return _del(node, str, strlen(str));
}

void _del(anagram_node * node, const char * str, unsigned int len) {
	if (len == 0) {
		node->valid = 0;
	} else {
		unsigned int index = (unsigned int)(str[0]) - base;
		if (node->nodes[index] == NULL) {
			return;
		} else {
			if (len == 1) {
				_del(node->nodes[index], NULL, len-1);
			} else {
				_del(node->nodes[index], (const char*)(&str[1]), len-1);
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

int __comparator(const void* a, const void* b) {
	return (*(char*)a - *(char*)b);
}

unsigned int anagrams(anagram_node * node, const char * str, unsigned int min, found_callback cb, void * data) {
	unsigned int len = strlen(str);
	// Make a copy of the string that we can modify, and then sort it
	char * _str = (char*)(malloc(len));
	memcpy(_str, str, len);
	qsort(_str, len, sizeof(char), __comparator);
	// Make a buffer where we'll store the string
	char * _buf = (char*)(malloc(len + 1));
	// Return
	unsigned int r = _anagrams(node, _str, len, _buf, 0, min, cb, data);
   free(_str);
   free(_buf);
   return r;
}

unsigned int _anagrams(anagram_node * node,
		char * str, unsigned int len,
		char * buf, unsigned int buf_len,
		unsigned int min,
		found_callback cb, void * data) {
	
	if (len == 0) {
	   if (node->valid && buf_len >= min) {
         buf[buf_len+1] = 0;
         cb(buf, buf_len, data);
         return 1;
	   }
      return 0;
	}
	
	char *       tmp   = (char *)(malloc(len-1));
	unsigned int sum   = 0;
	unsigned int count = 0;
	unsigned int index = 0;
	
	if (node->valid && buf_len >= min) {
		buf[buf_len+1] = 0;
		cb(buf, buf_len, data);
		sum += 1;
	}
	
   memcpy(tmp, (char*)(&str[1]), len-1);
	// Loop through each of the letters and search there.
	for (count = 0; count < len; ++count) {
      // We should skip over repeated letters
      if (count) {
         tmp[count-1] = str[count-1];
         if (str[count] == str[count-1]) {
            continue;
         }
      }
      
      index = (unsigned int)(str[count]) - base;
      //printf("Count: %i | Index: %i | Length: %i | BufLen: %i\n", count, index, len, buf_len);
      if (index < 26 && node->nodes[index] != NULL) {
			// Add this character to the buffer
			buf[buf_len] = str[count];
			// Find any sub-anagrams
         //printf("Sub-calling _anagrams\n");
			sum += _anagrams(node->nodes[index], tmp, len-1, buf, buf_len + 1, min, cb, data);
         buf[buf_len] = 0;
         //printf("Returned.\n");
         //printf("Chose index %i (%c) out of %s to append to %s, passing %s on\n", count, str[count], str, buf, tmp);
		}
	}
	
   free(tmp);
	return sum;
}

void loadFile(anagram_node * node, const char * path) {
	FILE * f = fopen(path, "r");
	char word[1024];
	while (fscanf(f, "%s", word) != EOF) {
    	printf("Loaded %s\n", word);
		insert(node, word);
	}
}