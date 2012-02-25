#define BUILDING_NODE_EXTENSION
#include <node.h>

#include <cstdlib>
#include <iostream>

#include "anagram-node-js.h"
#include "../src/anagram.h"

using namespace v8;

Node::Node() {
	initialize_node(&(this->_node), NULL);
};

Node::~Node() {
	destruct_node(&(this->_node));
};

Handle<Value> Node::Insert(const Arguments& args) {
	HandleScope scope;
	
	Node* obj = ObjectWrap::Unwrap<Node>(args.This());
	
	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Insert needs a string argument")));
		return scope.Close(Undefined());
	}
	
	insert(&(obj->_node), *String::AsciiValue(args[0]));
	return scope.Close(Boolean::New(true));
}

Handle<Value> Node::Del(const Arguments& args) {
	HandleScope scope;
	
	Node* obj = ObjectWrap::Unwrap<Node>(args.This());
	
	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Delete needs a string argument")));
		return scope.Close(Undefined());
	}
	
	del(&(obj->_node), *String::AsciiValue(args[0]));
	return scope.Close(Undefined());
}

Handle<Value> Node::Contains(const Arguments& args) {
	HandleScope scope;
	
	Node* obj = ObjectWrap::Unwrap<Node>(args.This());
	
	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Contains needs a string argument")));
		return scope.Close(Undefined());
	}
	
	return scope.Close(Boolean::New(contains(&(obj->_node), *String::AsciiValue(args[0]))));
}

void cb(const char * str, unsigned int len, void * data) {
    Local<Array> array = (*static_cast<Local<Array>*>(data));
    char * _str = (char*)(malloc(len + 1));
    memcpy(_str, str, len + 1);
    array->Set(array->Length(), String::New(_str));
}

Handle<Value> Node::Anagrams(const Arguments& args) {
	HandleScope scope;
	
	Node* obj = ObjectWrap::Unwrap<Node>(args.This());
	
	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Contains needs a string argument")));
		return scope.Close(Undefined());
	}
	
    unsigned int limit = 1;
    if (args.Length() > 1) {
        if (!args[1]->IsNumber()) {
            ThrowException(Exception::TypeError(String::New("Second argument must be a number")));
            return scope.Close(Undefined());
        } else {
            limit = args[1]->Uint32Value();
        }
    }
	
    Local<Array> results = Array::New();
	anagrams(&(obj->_node), *String::AsciiValue(args[0]), limit, cb, (void*)(&results));
	return scope.Close(results);
}

Handle<Value> Node::Load(const Arguments& args) {
	HandleScope scope;
	
	Node* obj = ObjectWrap::Unwrap<Node>(args.This());
	
	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Contains needs a string argument")));
		return scope.Close(Undefined());
	}
	
	loadFile(&(obj->_node), *String::AsciiValue(args[0]));
	return scope.Close(Boolean::New(true));
}

void Node::Init(Handle<Object> target) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Node"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	
	tpl->PrototypeTemplate()->Set(String::NewSymbol("insert"),
		FunctionTemplate::New(Insert)->GetFunction());
	
	tpl->PrototypeTemplate()->Set(String::NewSymbol("delete"),
		FunctionTemplate::New(Del)->GetFunction());
	
	tpl->PrototypeTemplate()->Set(String::NewSymbol("contains"),
		FunctionTemplate::New(Contains)->GetFunction());
	
	tpl->PrototypeTemplate()->Set(String::NewSymbol("anagrams"),
		FunctionTemplate::New(Anagrams)->GetFunction());
	
	tpl->PrototypeTemplate()->Set(String::NewSymbol("load"),
		FunctionTemplate::New(Load)->GetFunction());
	
	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	target->Set(String::NewSymbol("Node"), constructor);
}

Handle<Value> Node::New(const Arguments& args) {
	HandleScope scope;
	
	Node* obj = new Node();
	obj->Wrap(args.This());
	return args.This();
}
