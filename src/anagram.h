#ifndef ANAGRAM_H
#define ANAGRAM_H

#include <string.h>

/* This holds all the logic for an anagram prefix tree.
 * Oh, and for retrieving all anagrams. */

typedef struct _anagram_node {
	/* These are all the sub-nodes */
	struct _anagram_node * nodes[26];
	/* This points to the parent node */
	struct _anagram_node * parent;
	/* Whether or not the string up 'til now is valid */
	int valid;
} anagram_node;

/* This is the type of callback we expect for the anagram searching */
typedef void(*found_callback)(const char * str, unsigned int len, void * data);

/* Initialize an anagram node for use */
void initialize_node(anagram_node * node, anagram_node * parent);

/* Destructinate it */
void destruct_node(anagram_node * node);

/* Is this node a leaf? */
int leaf(const anagram_node * node);

/* Insert a string */
anagram_node * _insert(anagram_node * node, const char * str, unsigned int len);
anagram_node *  insert(anagram_node * node, const char * str);

/* Remove a string */
void _del(anagram_node * node, const char * str, unsigned int len);
void  del(anagram_node * node, const char * str);

/* Test for containment */
int _contains(anagram_node * node, const char * str, unsigned int len);
int  contains(anagram_node * node, const char * str);

/* Find all anagrams */
unsigned int anagrams(anagram_node * node, const char * str, found_callback cb, void * data);
/* This, however, is a little helper that will make it easier to 
 * do some of the searching. It allows characters to be swapped in
 * place, which makes it amenable to some performance gains. */
unsigned int _anagrams(anagram_node * node,
		char * str, unsigned int len,
		char * buf, unsigned int buf_len,
		found_callback cb, void * data);

/* =================================================
 * Convenience functions
 * ================================================= */

/* Load in a file of words */
void loadFile(anagram_node * node, const char * path);

#endif
