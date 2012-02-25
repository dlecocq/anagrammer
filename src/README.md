anagram
=======

My hope for this library is for it to be a useful resource in trie-based 
anagram programs. It is currently meant to deal with lowercase ascii
characters in the range 97 - 123.

API
===

The main type in this library is the `anagram_node`. Typically, you'll 
declare a single such node as the root of a `trie`, and then make queries
on that node, and not care about any of the other leaf or intermediate
nodes. There are a few important functions to call out as part of the API:

1. `insert` -- add a string to the repository
1. `del` -- remove a string
1. `contains` -- test for containment of a particular string
1. `anagrams` -- find all combinations of the provided letters in the repository

In addition, there's also a convenience method to read in space-separated
words from a file, called `loadFile`

Example
=======

Perhaps this library is best demonstrated by example.

	#include <stdio.h>
	
	#include "anagram.h"
	
	// The anagram functionality of this library makes heavy use
	// of callback functions. I don't know what you're going to
	// be doing with these anagrams, so I'm not going to declare
	// an array of results if you don't need them.
	void cb(const char * str, unsigned int str_len, void * data) {
		printf("Found anagram: %s", str);
	}
	
	int main() {
		anagram_node root;
		// You need to call initialize_node before using your node object
		initialize_node(&root, NULL);
	
		// Let's insert a few words
		insert(&root, "stop");
		insert(&root, "post");
		insert(&root, "pots");
		insert(&root, "tops");
		insert(&root, "opts");
		insert(&root, "spot");
		insert(&root, "howdy");
	
		// And we can check to see if a word is contained
		contains(&root, "spot"); // 1
		contains(&root, "foo" ); // 0
	
		// We didn't actually mean to add "howdy." Delete!
		del(&root, "howdy");
		
		// Let's find some anagrams! We'll provide the callback we 
		// described above. It will be invoked for each found anagram,
		// and this will return the total number of anagrams found
		anagrams(&root, "tpso", cb, NULL); // There are 6 anagrams
		
		// Actually, I have a list of space (newline, tab, space)
		// separated words stored in dictionary.txt. I'll just use that!
		loadFile(&root, "dictionary.txt");
		anagrams(&root, "onomotopoeia", cb, NULL);
	
		// And lastly, you should clean up after yourself
		destruct_node(&root);
		
		return 0;
	}
