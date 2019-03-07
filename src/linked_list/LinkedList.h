#pragma once

#include <vector>
#include <memory>

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
		if (itFirst) 
		{
			delete itFirst;
		}
		if (itLast) 
		{
			delete itLast;
		}
	}

	void add(T& o);
	size_t length() const;
	void clear();
	T* getLast() const;
	T* getFirst() const;
	bool remove(T& o);
	const Iterator<T>& begin()
	{ 
		this->itLast = new Iterator<T>(this->last->next);
		this->itFirst = new Iterator<T>(this->first);
		return *(this->itFirst);
	}
	const Iterator<T>& end() 
	{
		if (!itLast) 
		{
			this->itLast = new Iterator<T>(this->last->next);
		}
		return *(this->itLast); 
	}

private:
	friend Iterator<T>;
	void add(T* o);
	bool remove(T* o);
	bool remove(Node<T>* node);
	unsigned int size = 0;
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	Iterator<T>* itFirst = nullptr;
	Iterator<T>* itLast = nullptr;
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
	T* oPtr= new T(o);
	this->add(oPtr);
}

template<typename T>
inline size_t LinkedList<T>::length() const
{
	return size;
}

template<typename T>
inline void LinkedList<T>::clear()
{
	if (this->size > 0)
	{
		Node<T>* current = first;
		Node<T>* previous = nullptr;

		while (current)
		{
			previous = current;
			current = current->next;
			delete previous;
		}
	}
	this->size = 0;
}

template<typename T>
inline T* LinkedList<T>::getLast() const
{
	return last->obj;
}

template<typename T>
inline T * LinkedList<T>::getFirst() const
{
	return first->obj;
}

template<typename T>
inline bool LinkedList<T>::remove(T* o)
{
	if (this->size > 0)
	{
		Node<T>* current = this->first;
		Node<T>* previous = nullptr;

		while (current)
		{
			if (current == this->first && current->obj == o) {

				this->first = current->next;
				this->first->prev = nullptr;
				delete current;
				this->size--;
				return true;
			}
			else
			{
				previous = current;
				current = current->next;
				if (current->obj == o) {
					previous->next = current->next;
					current->next->prev = previous->next;
					if (!previous->next) {
						this->last = previous;
					}
					delete current;
					this->size--;
					return true;
				}
			}
		}
	}
	return false;
}

template<typename T>
inline bool LinkedList<T>::remove(T& o)
{
	return this->remove(&o);
}
