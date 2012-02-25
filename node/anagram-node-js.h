#ifndef ANAGRAM_NODE_H
#define ANAGRAM_NODE_H

#include <node.h>

// This is the underlying C library
#include "../src/anagram.h"

class Node : public node::ObjectWrap {
	public:
		static void Init(v8::Handle<v8::Object> target);
	
	private:
		Node();
		~Node();
		
		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		
		static v8::Handle<v8::Value> Insert(const v8::Arguments& args);
		static v8::Handle<v8::Value> Del(const v8::Arguments& args);
		static v8::Handle<v8::Value> Contains(const v8::Arguments& args);
		static v8::Handle<v8::Value> Anagrams(const v8::Arguments& args);
		
		anagram_node _node;
};

#endif