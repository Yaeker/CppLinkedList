#pragma once

#include <functional>


#include "Node.h"
#include "Iterator.h"

template <typename T>
class LinkedList
{
public:
	explicit LinkedList() { }
	virtual ~LinkedList()
	{
		this->clear();
		if (it) 
		{
			delete it;
		}
	}

	void add(T& o);
	size_t length() const;
	void clear();
	T* getLast() const;
	T* getFirst() const;
	bool remove(T& o);
	bool removeIf(bool(*predicate)(T));

	const Iterator<T>& begin()
	{ 
		if (this->it) {
			it->reset(this->first);
		}
		else
		{
			this->it = new Iterator<T>(this->first, this->size);
		}
		return *(this->it);
	}

private:
	void add(T* o);
	bool remove(T* o);
	unsigned int size = 0;
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	Iterator<T>* it = nullptr;
};

template<typename T>
inline void LinkedList<T>::add(T* o)
{
	Node<T>* el = new Node<T>(o);
	if (this->size == 0)
	{
		first = el;
		last = first;
	}
	else
	{
		last->next = el;
		el->prev = last;
		last = el;
	}
	this->size++;
}

template<typename T>
inline void LinkedList<T>::add(T& o)
{
	this->add(&o);
}

template<typename T>
inline size_t LinkedList<T>::length() const
{
	return size;
}

template<typename T>
inline void LinkedList<T>::clear()
{
	for (auto it = this->begin(); it.hasNext(); it++)
	{
		it.remove();
	}
}

template<typename T>
inline T* LinkedList<T>::getLast() const
{
	return last->obj;
}

template<typename T>
inline T* LinkedList<T>::getFirst() const
{
	return first->obj;
}

template<typename T>
inline bool LinkedList<T>::remove(T* o)
{
	for (auto it = this->begin(); it.hasNext(); it++)
	{
		if (o == *it) {
			it.remove();
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool LinkedList<T>::remove(T& o)
{
	return this->remove(&o);
}

template<typename T>
inline bool LinkedList<T>::removeIf(bool(*predicate)(T))
{
	for (auto it = this->begin(); it.hasNext(); it++)
	{
		if (predicate(*it)) {
			it.remove();
		}
	}
}
