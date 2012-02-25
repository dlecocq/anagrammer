#define BUILDING_NODE_EXTENSION

#include <node.h>
#include <v8.h>

#include "anagram-node-js.h"

using namespace v8;

void InitAll(Handle<Object> target) {
	Node::Init(target);
}

NODE_MODULE(anagram, InitAll)
