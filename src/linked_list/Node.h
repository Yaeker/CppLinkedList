#pragma once

template<typename T>
class Node
{
public:
	Node(T* o) : obj(o) {}
	virtual ~Node() { }
	Node* next = nullptr;
	Node* prev = nullptr;
	T* obj = nullptr;

private:
	
};

